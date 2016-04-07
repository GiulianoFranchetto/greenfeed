#include <iot_pull_data.h>
#include <stdio.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <manage_downstream.h>
#include <string.h>
#include <unistd.h>

/**
5. Downstream protocol
-----------------------

### 5.1. Sequence diagram ###

	+---------+                                                    +---------+
	| Gateway |                                                    | Server  |
	+---------+                                                    +---------+
	     | -----------------------------------\                         |
	     |-| Every N seconds (keepalive time) |                         |
	     | ------------------------------------                         |
	     |                                                              |
	     | PULL_DATA (token Y, MAC@)                                    |
	     |------------------------------------------------------------->|
	     |                                                              |
	     |                                           PULL_ACK (token Y) |
	     |<-------------------------------------------------------------|
	     |                                                              |

	+---------+                                                    +---------+
	| Gateway |                                                    | Server  |
	+---------+                                                    +---------+
	     |      ------------------------------------------------------\ |
	     |      | Anytime after first PULL_DATA for each packet to TX |-|
	     |      ------------------------------------------------------- |
	     |                                                              |
	     |                            PULL_RESP (token 0, JSON payload) |
	     |<-------------------------------------------------------------|
	     |                                                              |

*/

/**
### 5.2. PULL_DATA packet ###

That packet type is used by the gateway to poll data from the server.

This data exchange is initialized by the gateway because it might be
impossible for the server to send packets to the gateway if the gateway is
behind a NAT.

When the gateway initialize the exchange, the network route towards the
server will open and will allow for packets to flow both directions.
The gateway must periodically send PULL_DATA packets to be sure the network
route stays open for the server to be used at any time.

 Bytes  | Function
:------:|---------------------------------------------------------------------
 0      | protocol version = 1
 1-2    | random token
 3      | PULL_DATA identifier 0x02
 4-11   | Gateway unique identifier (MAC address)
 */
static void print_pull_data(iot_pull_data data) {
    printf("Protocol version: 0x%2.2X\n"
                   "Tokens: 0x%2.2X 0x%2.2X\n"
                   "Push ID: 0x%2.2X\n"
                   "MAC: 0x%2.2X 0x%2.2X 0x%2.2X 0x%2.2X 0x%2.2Xd 0x%2.2X 0x%2.2X 0x%2.2X\n"
                   "Message: %s\n",
           data.protocol_version,
           data.token[0], data.token[1],
           data.pull_data_id,
           data.MAC[0], data.MAC[1], data.MAC[2], data.MAC[3], data.MAC[4], data.MAC[5], data.MAC[6], data.MAC[7],
           data.json);
}

/*
### 5.3. PULL_ACK packet ###

That packet type is used by the server to confirm that the network route is
open and that the server can send PULL_RESP packets at any time.

 Bytes  | Function
:------:|---------------------------------------------------------------------
 0      | protocol version = 1
 1-2    | same token as the PULL_DATA packet to acknowledge
 3      | PULL_ACK identifier 0x04
 */

SOCKET down_sock;
struct sockaddr_in from;

static int send_pull_ack(SOCKET socket, iot_pull_data data, struct sockaddr_in from, socklen_t size) {
    byte ack[4];
    ack[0] = 1;
    ack[1] = data.token[0];
    ack[2] = data.token[1];
    ack[3] = 4;
    return sendto(socket, ack, 4, 0, (struct sockaddr *) &from, size) < 0 ? errno : 0;
}


void *manage_downstream(void *r) {
    struct sockaddr_in sin = {0};
    iot_pull_data pull_data = {{0}};
    socklen_t incomming_size = 0;

    printf("Lauching new worker: manage the downstream.\n");
    printf("Creating udp socket on port 3002.\n");

    down_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (down_sock == INVALID_SOCKET) {
        printf("Couldn't open the udp socket (err %d)\nExiting the main program.\n", errno);
        exit(errno);
    }

    printf("UDP interface configuration.\n");
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(3002);

    if (bind(down_sock, (struct sockaddr *) &sin, sizeof sin) == SOCKET_ERROR) {
        printf("Couldn't bind the newly created socket on port 3002 (err %d)\nExiting the main program.\n", errno);
        exit(errno);
    }

    printf("Initialization complete. Waiting for message from the IoT station.\n");

    while (!stop_thread_downstream) {

        while (recvfrom(down_sock, pull_data.msg, sizeof(pull_data.msg) - 1, 0, (struct sockaddr *) &from, &incomming_size) <
               0) {
            printf("Error when receiving downstream message (err %d). This is error %d over %d\n", errno,
                   downstream_error++, MAX_DOWNSTREAM_ERROR);

            if (downstream_error >= MAX_DOWNSTREAM_ERROR) {
                printf("Maximum error count reached. Trying to close the re-initialize the socket.\n");
            }
        }
        if (0 > send_pull_ack(down_sock, pull_data, from, incomming_size)) {
            printf("Error when sending ACK to IoT station\n");
        }

        memset(&pull_data, 0, sizeof(iot_pull_data));
        /*downstream_packet down_packet = {0};
        down_packet.frequency = 868.3;
        down_packet.rf_channel = 0;
        down_packet.i_polarization = false;
        down_packet.power = 14;
        down_packet.data = malloc(7);
        strcpy(down_packet.data, "Coucou");
        down_packet.payload_size = 6;

        send_downstream_message(down_sock, from, incomming_size, down_packet, true);*/

    }

    close(down_sock);
    return NULL;
}
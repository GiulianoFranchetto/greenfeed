#include <manage_upstream.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <parson.h>
#include <bson.h>
#include <mongo_connector.h>
#include <manage_downstream.h>

/**
3. Upstream protocol
---------------------

### 3.1. Sequence diagram ###

	+---------+                                                    +---------+
	| Gateway |                                                    | Server  |
	+---------+                                                    +---------+
	     | -----------------------------------\                         |
	     |-| When 1-N RF packets are received |                         |
	     | ------------------------------------                         |
	     |                                                              |
	     | PUSH_DATA (token X, GW MAC, JSON payload)                    |
	     |------------------------------------------------------------->|
	     |                                                              |
	     |                                           PUSH_ACK (token X) |
	     |<-------------------------------------------------------------|
	     |                              ------------------------------\ |
	     |                              | process packets *after* ack |-|
	     |                              ------------------------------- |
	     |                                                              |

 source : https://github.com/Lora-net/packet_forwarder/blob/master/PROTOCOL.TXT
*/

/*
### 3.2. PUSH_DATA packet ###

That packet type is used by the gateway mainly to forward the RF packets
received, and associated metadata, to the server.

 Bytes  | Function
:------:|---------------------------------------------------------------------
 0      | protocol version = 1
 1-2    | random token
 3      | PUSH_DATA identifier 0x00
 4-11   | Gateway unique identifier (MAC address)
 12-end | JSON object, starting with {, ending with }, see section 4
 */
static void print_push_data(iot_push_data data) {
    printf("Protocol version: 0x%2.2X\n"
                   "Tokens: 0x%2.2X 0x%2.2X\n"
                   "Push ID: 0x%2.2X\n"
                   "MAC: 0x%2.2X 0x%2.2X 0x%2.2X 0x%2.2X 0x%2.2Xd 0x%2.2X 0x%2.2X 0x%2.2X\n"
                   "Message: %s\n",
           data.protocol_version,
           data.token[0], data.token[1],
           data.push_data_id,
           data.MAC[0], data.MAC[1], data.MAC[2], data.MAC[3], data.MAC[4], data.MAC[5], data.MAC[6], data.MAC[7],
           data.json);
}

/*
### 3.3. PUSH_ACK packet ###

That packet type is used by the server to acknowledge immediately all the
PUSH_DATA packets received.

 Bytes  | Function
:------:|---------------------------------------------------------------------
 0      | protocol version = 1
 1-2    | same token as the PUSH_DATA packet to acknowledge
 3      | PUSH_ACK identifier 0x01
 */
static int send_push_ack(SOCKET socket, iot_push_data data, struct sockaddr_in from, socklen_t size) {
    byte ack[4];
    ack[0] = 1;
    ack[1] = data.token[0];
    ack[2] = data.token[1];
    ack[3] = 1;
    return sendto(socket, ack, 4, 0, (struct sockaddr *) &from, size) < 0 ? errno : 0;
}

static int understand_upstream_packet(upstream_packet packet) {
    JSON_Value *root_value = NULL;
    JSON_Object *root_object = NULL;
    JSON_Object *abri_object = NULL;
    JSON_Object *demande_object = NULL;

    char *payload;
    rxpk *cursor = packet.packets;
    bson_t *doc = bson_new();

    bson_oid_t oid;

    while (cursor != NULL) {
        payload = cursor->payload;
        root_value = json_parse_string(payload);
        if (json_value_get_type(root_value) != JSONObject) {
            printf("The json in push_data is bad formed\n");
            return JSON_BAD_FORMED;
        }
        root_object = json_value_get_object(root_value);
        abri_object = json_object_get_object(root_object, "abri");
        if (abri_object != NULL) {
            double vbat = json_object_dotget_number(abri_object, "v_bat");
            double pbat = json_object_dotget_number(abri_object, "p_bat");
            double mppto = json_object_dotget_number(abri_object, "mppt_o");
            time_t t = time(NULL);
            bson_oid_init(&oid, NULL);
            BSON_APPEND_OID (doc, "_id", &oid);
            BSON_APPEND_INT64(doc, "time", t);
            BSON_APPEND_DOUBLE(doc, "v_bat", vbat);
            BSON_APPEND_DOUBLE(doc, "p_bat", pbat);
            BSON_APPEND_DOUBLE(doc, "mppt_o", mppto);
            if (0 != mongo_add_document(mongo_client, "greenfeed", "abri", doc)) {
                return -1;
            };
            bson_free(doc);
        }

        demande_object = json_object_get_object(root_object, "demande");
        if (demande_object != NULL) {
            const char *uid = json_object_get_string(demande_object, "uid");
            query_result *result = malloc(sizeof(query_result));
            result->document = NULL;
            bson_t *request = bson_new();
            bson_t *query_sub_query_1 = bson_new();
            bson_t *query_sub_query_2 = bson_new();

            time_t timer;
            time(&timer);

            struct timeval tv;
            gettimeofday(&tv, NULL);
            BSON_APPEND_INT64(query_sub_query_1, "$lte", tv.tv_sec * 1000);
            BSON_APPEND_DOCUMENT(request, "starting_date", query_sub_query_1);

            BSON_APPEND_INT64(query_sub_query_2, "$gte", timer * 1000);
            BSON_APPEND_DOCUMENT(request, "ending_date", query_sub_query_2);

            BSON_APPEND_UTF8(request, "user_id", uid);

            printf("Request: %s\n", bson_as_json(request, NULL));
            if (0 == mongo_get_documents(mongo_client, "greenfeed", "booking", request, &result)) {
                downstream_packet down_packet = {0};
                down_packet.frequency = 868.3;
                down_packet.rf_channel = 0;
                down_packet.i_polarization = false;
                down_packet.power = 14;
                down_packet.data = malloc(18);
                if (result->document != NULL) {
                    JSON_Value *result_value = json_parse_string(result->document);
                    JSON_Object *result_object = json_value_get_object(result_value);
                    sprintf(down_packet.data, "{\"authorize\": 1, \"velo\": %d}", (int)json_object_get_number(result_object, "bike_id"));
                    json_value_free(result_value);
                }
                else {
                    strcpy(down_packet.data, "{\"authorize\": 0}");
                }
                down_packet.payload_size = 17;

                send_downstream_message(down_sock, from, sizeof(struct sockaddr_in), down_packet, true);
            }
            bson_free(query_sub_query_1);
            bson_free(query_sub_query_2);
            bson_free(request);
        }
        cursor = cursor->next;
        json_value_free(root_value);
    }
    return 0;
}

void *manage_upstream(void *r) {
    struct sockaddr_in sin = {0}, from = {0};
    SOCKET sock;
    iot_push_data push_data = {{0}};
    socklen_t incomming_size = 0;

    printf("Lauching new worker: manage the upstream.\n");
    printf("Creating udp socket on port 3001.\n");

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Couldn't open the udp socket (err %d)\nExiting the main program.\n", errno);
        exit(errno);
    }

    printf("UDP interface configuration.\n");
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(3001);

    if (bind(sock, (struct sockaddr *) &sin, sizeof sin) == SOCKET_ERROR) {
        printf("Couldn't bind the newly created socket on port 3001 (err %d)\nExiting the main program.\n", errno);
        exit(errno);
    }

    printf("Initialization complete. Waiting for message from the IoT station.\n");

    while (!stop_thread_upstream) {

        while (recvfrom(sock, push_data.msg, sizeof(push_data.msg) - 1, 0, (struct sockaddr *) &from, &incomming_size) <
               0) {
            printf("Error when receiving upstream message (err %d). This is error %d over %d\n", errno,
                   upstream_error++, MAX_UPSTREAM_ERROR);

            if (upstream_error >= MAX_UPSTREAM_ERROR) {
                printf("Maximum error count reached. Trying to close the re-initialize the socket.\n");
            }
        }
        printf("Sending ACK to IoT station\n");
        if (0 > send_push_ack(sock, push_data, from, incomming_size)) {
            printf("Error when sending ACK to IoT station\n");
        }
        printf("New message received from the IoT station (%d.%d.%d.%d)\n",
               from.sin_addr.s_addr & 0xFF,
               (from.sin_addr.s_addr & 0xFF00) >> 8,
               (from.sin_addr.s_addr & 0xFF0000) >> 16,
               (from.sin_addr.s_addr & 0xFF000000) >> 24);
        print_push_data(push_data);

        printf("Creating worker to parse the message\n");
        upstream_packet upstream = {{{0}}};

        if (0 > parse_upstream_json(push_data, &upstream)) {
            printf("Error while parsing push data\n");
        }
        else {
            print_upstream_packet(upstream);
            understand_upstream_packet(upstream);
            free_upstream_packet(&upstream);
            memset(&push_data, 0, sizeof(iot_push_data));
        }
    }
    printf("Stopping upstream management\n");
    close(sock);
    return NULL;
}
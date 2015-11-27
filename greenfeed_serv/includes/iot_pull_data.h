/**
 * \file includes/iot_pull_data.h
 * \brief This file defines a structure used to represent the pull_data message sent by the IoT station
 * \author Giuliano Franchetto
 * \date 30/09/2015
 * \version 1
 */

#ifndef GREENFEED_COMM_SERVER_IOT_IOT_PULL_DATA_H
#define GREENFEED_COMM_SERVER_IOT_IOT_PULL_DATA_H

#include <constants.h>
#include <types.h>

/**
 * Here is a part of the official documentation. The structure iot_pull_data is a C representation of the documentation
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

/**
 * \union iot_pull_data "includes/iot_pull_data.h"
 * An union is different from a structure in how it manages memory. In a structure, the memory scheme is as follow : <BR>
 * |_field A_|____________ field B__________| Padding |____Field C____| ... <BR>
 * Each field starts when the field before stops (some padding may be added, by that's an other topic).
 * An union typical scheme is as follow: <BR>
 * |_field A_|<BR>
 * |___________field B_________|<BR>
 * |field C|<BR>
 * All the fields start at the same address. <BR>
 * So, why an union? As the documentation says, the message received by the server is a 12 bytes, and each byte has its own
 * usage. We have to "cut" the message in part to get each packet of bytes. We could have done it by using the substring function,
 * but that's boring (need to manage memory allocation, calculate indexes ...). By using an union AND an internal structure, we can achieve
 * the same thing by way more easily.
 * We use an union to make the message and the internal structure to start at the same address. Then we use the structure memory scheme to create
 * fields which have the perfect size to "cut" the message where it needs to be. Let's see the result : <BR>
 * \image html iot_pull_data.png
 *
 * As we can see, the protocol_version field of the structure has the same content of the first byte of the message, and so does token ...
 */
typedef union{
    char msg[INCOMMING_MSG_SIZE];           /**< This is the field in which the message sent by the IoT station will be */
    struct __attribute__((__packed__)){     /**< This is the structure which will cut the message. To have some explanations about the packed attribute, go see Mr LALEVEE */
        byte protocol_version;
        byte token[2];
        byte pull_data_id;
        byte MAC[8];
        char json[INCOMMING_MSG_SIZE - 1 - 2 - 1 - 8];
    };
}iot_pull_data;
#endif //GREENFEED_COMM_SERVER_IOT_IOT_PULL_DATA_H

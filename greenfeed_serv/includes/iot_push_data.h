/**
 * \file includes/iot_push_data.h
 * \brief This file defines a structure used to represent the push_data message sent by the IoT station
 * \author Giuliano Franchetto
 * \date 30/09/2015
 * \version 1
 */

#ifndef GREENFEED_COMM_SERVER_IOT_PUSH_PACKET_H
#define GREENFEED_COMM_SERVER_IOT_PUSH_PACKET_H

#include <constants.h>
#include <types.h>

/**
 * Here is a part of the documentation
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

/**
 * \union iot_push_data "includes/iot_push_data.h"
 * \brief To have more information about this structure, look at the \ref iot_pull_data
 */
typedef union{
    char msg[INCOMMING_MSG_SIZE];
    struct __attribute__((__packed__))  {
        byte protocol_version;
        byte token[2];
        byte push_data_id;
        byte MAC[8];
        char json[INCOMMING_MSG_SIZE - 1 - 2 - 1 - 8];
    };
}iot_push_data;


#endif //GREENFEED_COMM_SERVER_IOT_PUSH_PACKET_H

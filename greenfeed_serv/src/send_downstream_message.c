#include <types.h>
#include <netinet/in.h>
#include <downstream_packet.h>
#include <stdio.h>
#include <parson.h>
#include <string.h>
#include <malloc.h>
#include <b64/cencode.h>

/**
### 5.4. PULL_RESP packet ###

That packet type is used by the server to send RF packets and associated
metadata that will have to be emitted by the gateway.

 Bytes  | Function
:------:|---------------------------------------------------------------------
 0      | protocol version = 1
 1-2    | unused bytes
 3      | PULL_RESP identifier 0x03
 4-end  | JSON object, starting with {, ending with }, see section 6



 Name |  Type  | Function
:----:|:------:|--------------------------------------------------------------
 imme | bool   | Send packet immediately (will ignore tmst & time)
 tmst | number | Send packet on a certain timestamp value (will ignore time)
 time | string | Send packet at a certain time (GPS synchronization required)
 freq | number | TX central frequency in MHz (unsigned float, Hz precision)
 rfch | number | Concentrator "RF chain" used for TX (unsigned integer)
 powe | number | TX output power in dBm (unsigned integer, dBm precision)
 modu | string | Modulation identifier "LORA" or "FSK"
 datr | string | LoRa datarate identifier (eg. SF12BW500)
 datr | number | FSK datarate (unsigned, in bits per second)
 codr | string | LoRa ECC coding rate identifier
 fdev | number | FSK frequency deviation (unsigned integer, in Hz)
 ipol | bool   | Lora modulation polarization inversion
 prea | number | RF preamble size (unsigned integer)
 size | number | RF packet payload size in bytes (unsigned integer)
 data | string | Base64 encoded RF packet payload, padding optional
 ncrc | bool   | If true, disable the CRC of the physical layer (optional)
 */

typedef struct __attribute__((__packed__)) {
    byte protocol;
    byte unused[2];
    byte id;
    char data[2048];
} pull_resp;

int send_downstream_message(SOCKET socket, struct sockaddr_in from, socklen_t size, downstream_packet packet,
                            bool use_minimum_data) {
    pull_resp response = {0};

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    base64_encodestate state_in;
    char *payload_b64;
    payload_b64 = calloc(1, packet.payload_size);
    base64_init_encodestate(&state_in);
    base64_encode_block(packet.data, packet.payload_size, payload_b64, &state_in);

    char *serialized_string = NULL;
    if (use_minimum_data) {
        json_object_dotset_boolean(root_object, "txpk.imme", true);
        json_object_dotset_number(root_object, "txpk.freq", packet.frequency);
        json_object_dotset_number(root_object, "txpk.powe", packet.power);
        json_object_dotset_number(root_object, "txpk.rfch", packet.rf_channel);
        json_object_dotset_string(root_object, "txpk.modu", "LORA");
        json_object_dotset_string(root_object, "txpk.datr", "SF12BW500");
        json_object_dotset_string(root_object, "txpk.codr", "4/8");
        json_object_dotset_number(root_object, "txpk.size", strlen(packet.data));
        json_object_dotset_string(root_object, "txpk.data", payload_b64);
        serialized_string = json_serialize_to_string(root_value);

        response.protocol = 1;
        response.id = 3;
        strcpy(response.data, serialized_string);

        printf("Sending message %s to IoT station (ascii)\n", packet.data);
        printf("Sending %s to IoT station\n", response.data);
        sendto(socket, &response, sizeof(response), 0, (struct sockaddr *) &from, size);

        json_free_serialized_string(serialized_string);
        json_value_free(root_value);
    }

    return 0;
}
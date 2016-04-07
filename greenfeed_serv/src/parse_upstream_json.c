#include "iot_push_data.h"
#include <parson.h>
#include <stdio.h>
#include <upstream_packet.h>
#include <string.h>
#include <malloc.h>
#include <b64/cdecode.h>

#define OR_NULL_STR(x)      (x == NULL? "" : (char*)x)  // Need a cast to remove the const identifier

int parse_upstream_json(iot_push_data data, upstream_packet *packet) {
    JSON_Value *root_value = NULL;
    JSON_Object *root_object = NULL;
    JSON_Object *stat_object = NULL;
    JSON_Object *rxpk_object = NULL;
    JSON_Array *rx_object = NULL;
    int i = 0;

    root_value = json_parse_string(data.json);
    if (json_value_get_type(root_value) != JSONObject) {
        printf("The json in push_data is bad formed\n");
        return JSON_BAD_FORMED;
    }

    root_object = json_value_get_object(root_value);
    stat_object = json_object_get_object(root_object, "stat");
    if (stat_object != NULL) {
        strncpy((*packet).stat.time, OR_NULL_STR(json_object_get_string(stat_object, "time")), 25);
        (*packet).stat.latitude = json_object_get_number(stat_object, "lati");
        (*packet).stat.longitude = json_object_get_number(stat_object, "long");
        (*packet).stat.altitude = json_object_get_number(stat_object, "alti");
        (*packet).stat.nb_packet = (unsigned int) json_object_get_number(stat_object, "rxnb");
        (*packet).stat.nb_packet_ok = (unsigned int) json_object_get_number(stat_object, "rxok");
        (*packet).stat.nb_packet_forwarded = (unsigned int) json_object_get_number(stat_object, "rxfw");
        (*packet).stat.cpt_up_ack = json_object_get_number(stat_object, "ackr");
        (*packet).stat.nb_packet_down = (unsigned int) json_object_get_number(stat_object, "dwnb");
        (*packet).stat.nb_packet_sent = (unsigned int) json_object_get_number(stat_object, "txnb");
    }
    else {
        printf("No stat entry in json. Continuing\n");
    }

    rx_object = json_object_get_array(root_object, "rxpk");
    if (rx_object != NULL) {
        for (i = 0; i < json_array_get_count(rx_object); i++) {
            rxpk_object = json_array_get_object(rx_object, (size_t) i);
            rxpk *pk = calloc(1, sizeof(rxpk));
            strncpy(pk->time, OR_NULL_STR(json_object_get_string(rxpk_object, "time")), 35);
            pk->tmst = (unsigned int) json_object_get_number(rxpk_object, "tmst");
            pk->channel = (unsigned int) json_object_get_number(rxpk_object, "chan");
            pk->rf_channel = (unsigned int) json_object_get_number(rxpk_object, "rfch");
            pk->freq = json_object_get_number(rxpk_object, "freq");
            pk->stat = (unsigned int) json_object_get_number(rxpk_object, "stat");
            strncpy(pk->modulation, OR_NULL_STR(json_object_get_string(rxpk_object, "modu")), 5);
            if (strcmp(pk->modulation, "FSK") == 0)
                pk->fsk_datarate = (unsigned int) json_object_get_number(rxpk_object, "datr");
            else
                strncpy(pk->datarate, OR_NULL_STR(json_object_get_string(rxpk_object, "datr")), 15);
            strncpy(pk->coding_rate, OR_NULL_STR(json_object_get_string(rxpk_object, "codr")), 10);
            pk->rssi = (int) json_object_get_number(rxpk_object, "rssi");
            pk->snr = json_object_get_number(rxpk_object, "lsnr");
            pk->packet_size = (unsigned int) json_object_get_number(rxpk_object, "size");
            pk->payload = calloc(1, strlen(OR_NULL_STR(json_object_get_string(rxpk_object, "data")) + 1));
            base64_decodestate state_in;
            base64_init_decodestate(&state_in);
            base64_decode_block(OR_NULL_STR(json_object_get_string(rxpk_object, "data")),
                                strlen(OR_NULL_STR(json_object_get_string(rxpk_object, "data"))) + 1, pk->payload,
                                &state_in);
            //strcpy(pk->payload, OR_NULL_STR(json_object_get_string(rxpk_object, "data")));
            pk->next = NULL;
            if (i == 0) {
                (*packet).packets = pk;
                (*packet).packets->next = NULL;
            }
            else {
                pk->next = (*packet).packets;
                (*packet).packets = pk;
            }
        }
    }
    else {
        printf("No rxpk entry in json. Ending\n");
    }

    json_value_free(root_value);
    return 0;
}
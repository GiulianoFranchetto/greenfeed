/**
 * \file includes/downstream_packet.h
 * \brief This file defines the structure "downstream_packet"
 * \author Giuliano Franchetto
 * \date 30/09/2015
 * \version 1
 *
 * The reader can find the official documentation on this url: https://github.com/Lora-net/packet_forwarder/blob/master/PROTOCOL.TXT
 */

#ifndef GREENFEED_COMM_SERVER_IOT_DOWNSTREAM_PACKET_H
#define GREENFEED_COMM_SERVER_IOT_DOWNSTREAM_PACKET_H

#include <stdbool.h>

/**
 * \struct downstream_packet includes/downstream_packet.h
 * \brief This structure represents a package that must be sent to the IoT station to make it send a LoRa message
 *        Some of these fields are optional
 */
typedef struct{
    bool            send_now;       /**< If this field is equal to true, the packet will be sent by the IoT station immediately */
    long            timestamp;      /**< If the send_now field is set to false, the packet will be sent when the current date of the IoT station reaches this value */
    char            time[35];       /**< Same use that the timestamp field. The representation of the date is different */
    double          frequency;      /**< The central frequency used when the packet is emitted */
    unsigned int    rf_channel;     /**< The channel the IoT station will use to emit the packet */
    unsigned int    power;          /**< The power used by the antenna to emit the packet */
    char            modulation[5];  /**< The LoRa modulation used: LORA or FSK. Other values will be discarded */
    char            datarate[15];   /**< The datarate used in case the LORA modulation is chosen */
    unsigned int    fsk_datarate;   /**< The datarate used in case the FSK modulation is chosen */
    char            code_rate[10];  /**< The code rate used to emit the packet, example 4/5 */
    unsigned int    fsk_deviation;  /**< The FSK frequency deviation */
    bool            i_polarization; /**< If this field is set to true, the LoRa modulation polarization will be inversed */
    unsigned int    rf_preamble;    /**< The RF preamble size */
    unsigned int    payload_size;   /**< The payload size in bytes */
    char            *data;          /**< The actual payload in base64 */
    bool            disable_CRC;    /**< If this field is set to true, the CRC check will be disabled (should always be set to false!) */
} downstream_packet;
#endif //GREENFEED_COMM_SERVER_IOT_DOWNSTREAM_PACKET_H

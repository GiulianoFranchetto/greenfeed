#include <upstream_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <b64/cdecode.h>


/*
  Name |  Type  | Function
:----:|:------:|--------------------------------------------------------------
 time | string | UTC time of pkt RX, us precision, ISO 8601 'compact' format
 tmst | number | Internal timestamp of "RX finished" event (32b unsigned)
 freq | number | RX central frequency in MHz (unsigned float, Hz precision)
 chan | number | Concentrator "IF" channel used for RX (unsigned integer)
 rfch | number | Concentrator "RF chain" used for RX (unsigned integer)
 stat | number | CRC status: 1 = OK, -1 = fail, 0 = no CRC
 modu | string | Modulation identifier "LORA" or "FSK"
 datr | string | LoRa datarate identifier (eg. SF12BW500)
 datr | number | FSK datarate (unsigned, in bits per second)
 codr | string | LoRa ECC coding rate identifier
 rssi | number | RSSI in dBm (signed integer, 1 dB precision)
 lsnr | number | Lora SNR ratio in dB (signed float, 0.1 dB precision)
 size | number | RF packet payload size in bytes (unsigned integer)
 data | string | Base64 encoded RF packet payload, padded
 */
void print_upstream_packet(upstream_packet packet)
{
    printf("Stat:\n"
                   "******************\n"
                   "time: %s\n"
                   "latitude: %f\n"
                   "longitude: %f\n"
                   "altitude: %f\n"
                   "number received: %d\n"
                   "number OK: %d\n"
                   "number forwarded: %d\n"
                   "ACK percentage: %f\n"
                   "dowlink received: %d\n"
                   "number emitted: %d\n",
           packet.stat.time,
           packet.stat.latitude,
           packet.stat.longitude,
           packet.stat.altitude,
           packet.stat.nb_packet,
           packet.stat.nb_packet_ok,
           packet.stat.nb_packet_forwarded,
           packet.stat.cpt_up_ack,
           packet.stat.nb_packet_down,
           packet.stat.nb_packet_sent);

    rxpk *cursor = packet.packets;

    while (cursor != NULL) {
        char tmp_dr[10];
        if (strcmp(cursor->modulation, "FSK") == 0)
            sprintf(tmp_dr, "%d", cursor->fsk_datarate);
        else
            sprintf(tmp_dr, "%s", cursor->datarate);
        printf("Packet:\n"
                       "******************\n"
                       "time: %s\n"
                       "internal timestamp: %d\n"
                       "frequency: %f\n"
                       "channel: %d\n"
                       "RF chan: %d\n"
                       "CRC status: %d\n"
                       "modulation: %s\n"
                       "datarate: %s\n"
                       "coding rate: %s\n"
                       "rssi: %d\n"
                       "SRN radio: %f\n"
                       "packet size: %d\n"
                       "payload: %s\n",
               cursor->time,
               cursor->tmst,
               cursor->freq,
               cursor->channel,
               cursor->rf_channel,
               cursor->stat,
               cursor->modulation,
               tmp_dr,
               cursor->coding_rate,
               cursor->rssi,
               cursor->snr,
               cursor->packet_size,
               cursor->payload
        );
        cursor = cursor->next;
    }

}
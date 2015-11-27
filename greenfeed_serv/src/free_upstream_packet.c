#include <upstream_packet.h>
#include <malloc.h>

void free_upstream_packet(upstream_packet *packet)
{
    rxpk *next_node = NULL;

    if (packet->packets == NULL) {
        return;
    }

    next_node = packet->packets->next;
    free(packet->packets->payload);
    free(packet->packets);
    packet->packets = next_node;
    free_upstream_packet(packet);
}
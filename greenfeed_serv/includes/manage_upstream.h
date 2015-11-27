/**
 * \file includes/manage_upstream.h
 * \brief This file defines some function prototypes and global variables
 * \author Giuliano Franchetto
 * \date 30/09/2015
 * \version 1
 */

#ifndef GREENFEED_COMM_SERVER_IOT_MANAGE_UPSTREAM_H
#define GREENFEED_COMM_SERVER_IOT_MANAGE_UPSTREAM_H

#include <pthread.h>
#include <stdbool.h>
#include <iot_push_data.h>
#include <upstream_packet.h>

/**
 * \fn void *manage_upstream(void *r)
 * \brief The thread routine called by main
 * \param r     unused param
 * \return      NULL
 */
void* manage_upstream(void* args);

/**
 * \fn int parse_upstream_json(iot_push_data data, upstream_packet *packet)
 * \brief This function parses a incoming message from the IoT station
 * \param data  The \ref iot_push_data representing the IoT packet
 * \param *packet   a pointer to a \ref upstream_packet which will be filled by the function
 * \return 0 on success, errno on error
 */
int parse_upstream_json(iot_push_data data, upstream_packet *packet);

/**
 * \fn void print_upstream_packet(upstream_packet packet)
 * \brief Print a nice message on the console which the data contained in the \ref upstream_packet
 * \param packet    the packet to print
 * \return nothing
 */
void print_upstream_packet(upstream_packet packet);

/**
 * \fn void free_upstream_packet(upstream_packet *packet)
 * \brief This function frees the linked list in the \ref upstream_packet packet
 * \param *packet   A pointer to the \ref upstream_packet to free
 * \return nothing
 */
void free_upstream_packet(upstream_packet *packet);

extern pthread_t thread_manage_upstream;    /**< The thread used by the manage_upstream routine */
extern bool stop_thread_upstream;           /**< This varibale must be set to true to stop the thread */
extern int upstream_error;                  /**< The number of error the upstream thread did */

#endif //GREENFEED_COMM_SERVER_IOT_MANAGE_UPSTREAM_H

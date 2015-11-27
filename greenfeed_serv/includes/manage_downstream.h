/**
 * \file includes/manage_downstream.h
 * \brief This file defines some function prototypes and global variables
 * \author Giuliano Franchetto
 * \date 30/09/2015
 * \version 1
 */
#ifndef GREENFEED_COMM_SERVER_IOT_MANAGE_DOWNSTREAM_H
#define GREENFEED_COMM_SERVER_IOT_MANAGE_DOWNSTREAM_H

#include <stdbool.h>
#include <downstream_packet.h>
#include <pthread.h>
#include <netinet/in.h>

/**
 * \fn int send_downstream_message(SOCKET socket, struct sockaddr_in from, socklen_t size, downstream_packet packet, bool use_minimum_data);
 * \brief This function send a message to the IoT station. This message will next be sent in LoRa
 * \param socket    the udp socket with the IoT station
 * \param from      a sockaddr_in structure which defines the communication with the IoT station
 * \param size
 * \param packet    the packet to send to the IoT station, see \ref downstream_packet
 * \param use_minimum_data  packet will be filled with default data in some fields. Needs to be set to true for the moment
 *
 * \return  0 on success, or the errno code
 */
int send_downstream_message(SOCKET socket, struct sockaddr_in from, socklen_t size, downstream_packet packet, bool use_minimum_data);

/**
 * \fn void *manage_downstream(void *r)
 * \brief The thread routine called by main
 * \param r     unused param
 * \return      NULL
 */
void *manage_downstream(void *r);

extern pthread_t thread_manage_downstream;  /**< The pthread_t used for the manage_downstream thread */
extern bool stop_thread_downstream;         /**< A boolean which must set to true to stop the thread */
extern int downstream_error;                /**< The number of error this thread made */

#endif //GREENFEED_COMM_SERVER_IOT_MANAGE_DOWNSTREAM_H

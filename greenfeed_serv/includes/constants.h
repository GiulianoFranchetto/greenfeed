/**
 * \file includes/constants.h
 * \brief This file defines some constants used in the program
 * \author Giuliano Franchetto
 * \date 30/09/2015
 * \version 1
 */

#ifndef GREENFEED_COMM_SERVER_IOT_CONSTANTS_H
#define GREENFEED_COMM_SERVER_IOT_CONSTANTS_H

/**
 * \def MAX_UPSTREAM_ERROR
 * This field defines the number of allowed error before closing the upstream socket with the IoT station
 */
#define MAX_UPSTREAM_ERROR      5

/**
 * \def MAX_DOWNSTREAM_ERROR
 * This field defines the number of allowed error before closing the downstream socket with the IoT station
 */
#define MAX_DOWNSTREAM_ERROR    5

/**
 * \def INCOMMING_MSG_SIZE
 * This is the maximum size of a packet sent by the IoT station to the program. This is not robust, but for the first
 * version, this will do it
 */
#define INCOMMING_MSG_SIZE      2048

/**
 * \def INVALID_SOCKET
 * Error code returned when creating a socket fails
 */
#define INVALID_SOCKET          -1

/**
 * \def SOCKET_ERROR
 * Error code returned when a read/write operation fails
 */
#define SOCKET_ERROR            -2

/**
 * \def JSON_BAD_FORMED
 * Error code returned when a JSON sent by the IoT station is malformed
 */
#define JSON_BAD_FORMED         -3

#endif //GREENFEED_COMM_SERVER_IOT_CONSTANTS_H

/**
 * \file main.c
 * \brief This file is the entry of the main program to communicate with the Kerlink IoT station.
 * \author Giuliano Franchetto
 * \version 1.0
 * \date 09/30/2015
 */

#include <signal.h>
#include <manage_upstream.h>
#include <manage_downstream.h>
#include <mongo_connector.h>

pthread_t thread_manage_upstream, thread_manage_downstream;
bool stop_thread_upstream = false, stop_thread_downstream = false;
int upstream_error = 0, downstream_error = 0;
mongoc_client_t *mongo_client;

void signal_int(int sig)
{
    stop_thread_upstream = true;
    stop_thread_downstream = true;
    pthread_cancel(thread_manage_upstream);
    pthread_cancel(thread_manage_downstream);
}

int main()
{
    signal(SIGINT, signal_int);
    printf("Connection to the database\n");
    mongo_client = mongo_connection("mongodb://localhost:27017/");
    if(mongo_client == NULL){
        printf("Could not open a connection with the database. Exiting the program");
        exit(-2);
    }
    pthread_create(&thread_manage_upstream, 0, manage_upstream, NULL);
    pthread_create(&thread_manage_downstream, 0, manage_downstream, NULL);
    pthread_join(thread_manage_upstream, NULL);
    pthread_join(thread_manage_downstream, NULL);
    return 0;
}
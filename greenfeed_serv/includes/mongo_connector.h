#ifndef GREENFEED_COMM_SERVER_IOT_MONGO_CONNECTOR_H
#define GREENFEED_COMM_SERVER_IOT_MONGO_CONNECTOR_H

#include <bson.h>
#include <mongoc.h>
#include <query_result.h>

int mongo_get_documents(mongoc_client_t* client, char* database, char* collection_name, bson_t* query, query_result** result);
int mongo_add_document(mongoc_client_t* client, char* database, char* collection_name, bson_t* document);
mongoc_client_t* mongo_connection(char* url);
void mongo_clear_query_result(query_result** query);

extern mongoc_client_t *mongo_client;
#endif //GREENFEED_COMM_SERVER_IOT_MONGO_CONNECTOR_H

#include <stddef.h>
#include <stdio.h>
#include <mongoc.h>
#include <query_result.h>

mongoc_client_t* mongo_connection(char* url){
    if(url == NULL)
        return NULL;
    mongoc_init ();
    return mongoc_client_new(url);
}

int mongo_add_document(mongoc_client_t* client, char* database, char* collection_name, bson_t* document){
    mongoc_collection_t *collection;
    bson_error_t error;

    collection = mongoc_client_get_collection(client, database, collection_name);

    if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, document, NULL, &error)) {
        printf ("%s\n", error.message);
        return -1;
    }
    mongoc_collection_destroy (collection);
    return 0;
}

int mongo_get_documents(mongoc_client_t* client, char* database, char* collection_name, bson_t* query, query_result** result){
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    char *str;
    int index = 0;
    collection = mongoc_client_get_collection (client, database, collection_name);

    cursor = mongoc_collection_find (collection, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);

    query_result* current = *result;
    while (mongoc_cursor_next (cursor, &doc)) {
        str = bson_as_json (doc, NULL);
        if(index == 0) {
            (*result)->document = malloc(strlen(str) + 1);
            strcpy((*result)->document, str);
            (*result)->next = NULL;
        }
        else {
            current->next = malloc(sizeof(query_result));
            current->next->document = malloc(strlen(str) + 1);
            strcpy(current->next->document, str);
            current->next->next = NULL;
            current = current->next;
        }
        index++;
        bson_free(str);
    }

    mongoc_cursor_destroy (cursor);
    mongoc_collection_destroy (collection);
    return 0;
}

void mongo_clear_query_result(query_result** query){
    query_result *next_node = NULL;

    if (*query == NULL) {
        return;
    }

    next_node = (*query)->next;
    free((*query)->document);
    free(*query);
    *query = next_node;
    mongo_clear_query_result(query);

}
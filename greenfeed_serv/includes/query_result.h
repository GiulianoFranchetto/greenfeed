#ifndef GREENFEED_COMM_SERVER_IOT_QUERY_RESULT_H
#define GREENFEED_COMM_SERVER_IOT_QUERY_RESULT_H

typedef struct node{
    char* document;
    struct node* next;
}query_result;

#endif //GREENFEED_COMM_SERVER_IOT_QUERY_RESULT_H

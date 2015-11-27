cmake_minimum_required(VERSION 3.3)
project(greenfeed_comm_server_iot)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -g")

include_directories(includes)
include_directories(/usr/local/include)
include_directories(parson)
set(SOURCE_FILES main.c src/manage_upstream.c includes/manage_upstream.h includes/types.h includes/constants.h includes/iot_push_data.h parson/parson.c parson/parson.h includes/upstream_packet.h src/parse_upstream_json.c src/print_upstream_packet.c src/free_upstream_packet.c includes/manage_downstream.h includes/iot_pull_data.h src/manage_downstream.c src/send_downstream_message.c includes/downstream_packet.h src/mongo_connector.c includes/mongo_connector.h includes/query_result.h)
add_executable(greenfeed_comm_server_iot ${SOURCE_FILES} includes/b64/cdecode.h includes/b64/cencode.h)
target_link_libraries(greenfeed_comm_server_iot pthread mongoc-1.0 bson-1.0)
target_link_libraries(greenfeed_comm_server_iot ${CMAKE_SOURCE_DIR}/lib/libb64.a)
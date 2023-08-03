include_directories(CMAKE_CURRENT_LIST_DIR)
file(GLOB_RECURSE gateway_files *.cpp)
add_executable(gate ${gateway_files})
target_link_libraries(gate muduo_net muduo_base pthread server_common_lib 
cpp_redis tacopie server_db_lib  yaml-cpp msg_grpc_proto_lib conversation_grpc_proto_lib
auth_grpc_proto_lib  group_grpc_proto_lib gateway_grpc_proto_lib )
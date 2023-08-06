file(GLOB api_files "*.cpp")

add_executable(api ${api_files})

include_directories(CMAKE_CURRENT_LIST_DIR)


target_link_libraries(api pthread)
target_link_libraries(api msg_grpc_proto_lib auth_grpc_proto_lib conversation_grpc_proto_lib
group_grpc_proto_lib grpc_proto_lib muduo_base) 
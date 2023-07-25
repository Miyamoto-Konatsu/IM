cmake_minimum_required(VERSION 3.6.1)
project(conversationServer)

include_directories("${CMAKE_CURRENT_LIST_DIR}")
# 添加你的项目源文件
add_executable(conversationServer conversation.cpp  ${server_common_files})

# 链接 gRPC 库
target_link_libraries(conversationServer conversation_grpc_proto_lib msg_grpc_proto_lib server_db_lib)
# 链接 redis ,yaml库
target_link_libraries(conversationServer cpp_redis yaml-cpp tacopie)

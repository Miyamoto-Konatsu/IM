cmake_minimum_required(VERSION 3.6.1)
project(conversationClient)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

# 添加你的项目源文件
add_executable(conversationClient conversation.cpp)

# 链接 gRPC 库
target_link_libraries(conversationClient PUBLIC conversation_grpc_proto_lib 
msg_grpc_proto_lib server_common_lib)
# grpc_proto_lib

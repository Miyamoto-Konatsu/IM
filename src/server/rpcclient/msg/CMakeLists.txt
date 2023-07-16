cmake_minimum_required(VERSION 3.6.1)
project(msgClient)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

add_executable(msgClient msg.cpp)

# 链接 gRPC 库
target_link_libraries(msgClient PUBLIC msg_grpc_proto_lib )

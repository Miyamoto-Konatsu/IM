cmake_minimum_required(VERSION 3.6.1)
project(groupClient)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

add_executable(groupClient group.cpp)

# 链接 gRPC 库
target_link_libraries(groupClient PUBLIC group_grpc_proto_lib )

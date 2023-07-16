cmake_minimum_required(VERSION 3.6.1)
project(authClient)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

# 添加你的项目源文件
add_executable(authClient auth.cpp)

# 链接 gRPC 库
target_link_libraries(authClient PUBLIC auth_grpc_proto_lib )
# grpc_proto_lib

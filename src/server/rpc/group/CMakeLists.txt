cmake_minimum_required(VERSION 3.6.1)
project(groupServer)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

# 添加你的项目源文件
add_executable(groupServer group.cpp  ${server_common_files})

# 链接 gRPC 库
target_link_libraries(groupServer group_grpc_proto_lib)
# 链接 redis ,yaml库
target_link_libraries(groupServer cpp_redis yaml-cpp tacopie server_mq_lib server_db_lib )

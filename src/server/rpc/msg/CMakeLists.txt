cmake_minimum_required(VERSION 3.6.1)
project(msgServer)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

# 添加你的项目源文件
add_executable(msgServer msg.cpp  ${server_common_files})

# 链接 gRPC 库
target_link_libraries(msgServer msg_grpc_proto_lib)
# 链接 redis ,yaml库
target_link_libraries(msgServer cpp_redis yaml-cpp tacopie server_mq_lib server_db_lib)

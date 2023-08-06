cmake_minimum_required(VERSION 3.6.1)
project(userServer)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

# 添加你的项目源文件
add_executable(userServer user.cpp  )

# 链接 gRPC 库
target_link_libraries(userServer grpc_proto_lib )
# 链接 redis ,yaml库
target_link_libraries(userServer  cpp_redis yaml-cpp tacopie server_common_lib server_db_lib muduo_base)

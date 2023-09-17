cmake_minimum_required(VERSION 3.6.1)
project(persistServer)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

file(GLOB_RECURSE server_persist_files "./*.cpp")
# 添加你的项目源文件
add_executable(persistServer ${server_persist_files}  ${server_common_files})

# 链接 gRPC 库
target_link_libraries(persistServer muduo_base grpc_proto_lib)
# 链接 redis ,yaml库
target_link_libraries(persistServer cpp_redis yaml-cpp tacopie server_mq_lib server_db_lib)
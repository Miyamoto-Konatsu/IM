cmake_minimum_required(VERSION 3.6.1)
project(pushServer)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

file(GLOB_RECURSE server_push_files "./*.cpp")
# 添加你的项目源文件
add_executable(pushServer ${server_push_files} )

# 链接 gRPC 库
target_link_libraries(pushServer msg_grpc_proto_lib gateway_grpc_proto_lib group_grpc_proto_lib  grpc_proto_lib)
# 链接 redis ,yaml库
target_link_libraries(pushServer cpp_redis yaml-cpp tacopie server_mq_lib server_db_lib server_common_lib pthread)

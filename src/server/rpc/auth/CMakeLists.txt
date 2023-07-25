cmake_minimum_required(VERSION 3.6.1)
project(auth)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

set(token_vefile "${CMAKE_CURRENT_LIST_DIR}/../../common/token/jwt_token.cpp")

# 添加你的项目源文件
add_executable(authServer auth.cpp ${token_vefile}  ${server_common_files})

# 链接 gRPC 库
target_link_libraries(authServer auth_grpc_proto_lib msg_grpc_proto_lib server_db_lib)
# 链接 redis ,yaml库
target_link_libraries(authServer cpp_redis yaml-cpp tacopie)

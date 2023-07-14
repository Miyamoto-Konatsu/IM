cmake_minimum_required(VERSION 3.6.1)
project(auth)

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_LIST_DIR}")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../../../common/token")
set(token_vefile "${CMAKE_CURRENT_LIST_DIR}/../../../common/token/jwt_token.cpp")

# 添加你的项目源文件
add_executable(MyExecutable auth.cpp ${token_vefile})

# 链接 gRPC 库
target_link_libraries(MyExecutable auth_grpc_proto)


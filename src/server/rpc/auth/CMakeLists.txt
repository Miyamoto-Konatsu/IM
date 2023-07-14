cmake_minimum_required(VERSION 3.6.1)
project(auth)

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_LIST_DIR}")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../../../common/token")
set(token_vefile "${CMAKE_CURRENT_LIST_DIR}/../../../common/token/jwt_token.cpp")

# 包含 gRPC 的头文件目录
include_directories(${gRPC_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_LIST_DIR}/../../../proto/auth)
set(DIR_SRCS "")
aux_source_directory("${CMAKE_CURRENT_LIST_DIR}/../../../proto/auth" DIR_SRCS)
# 添加你的项目源文件
add_executable(MyExecutable auth.cpp ${token_vefile})
add_library(auth_grpc_proto
  ${DIR_SRCS})
# 链接 gRPC 库
target_link_libraries(MyExecutable auth_grpc_proto ${gRPC_LIBRARIES})
# auth_grpc_proto

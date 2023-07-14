
aux_source_directory("${CMAKE_CURRENT_LIST_DIR}/../proto/auth" DIR_SRCS)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../proto/auth)

# 包含 gRPC 的头文件目录
include_directories(${gRPC_INCLUDE_DIRS})

add_library(auth_grpc_proto ${DIR_SRCS})

target_link_libraries(auth_grpc_proto PUBLIC
gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotobuf
)
add_subdirectory(rpc/auth)
add_subdirectory(rpcclient/auth)
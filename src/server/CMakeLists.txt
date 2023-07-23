
# 包含 gRPC 的头文件目录
include_directories(${gRPC_INCLUDE_DIRS})

# 包含 protobuf 生成的头文件目录，生成对应链接库
foreach(_target
    auth
    msg
    )
    aux_source_directory("${CMAKE_CURRENT_LIST_DIR}/../proto/${_target}" ${_target}_PROTO_DIR_SRCS)
    include_directories(${CMAKE_CURRENT_LIST_DIR}/../proto/${_target})
    add_library(${_target}_grpc_proto_lib ${${_target}_PROTO_DIR_SRCS})
    target_link_libraries(${_target}_grpc_proto_lib PUBLIC
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotobuf
    )
endforeach()


include_directories("${CMAKE_CURRENT_LIST_DIR}/common/token")

include_directories("${CMAKE_CURRENT_LIST_DIR}/common")
file(GLOB_RECURSE server_common_files "./common/*.cpp")

include_directories("${CMAKE_CURRENT_LIST_DIR}/db")
# 递归地获取db目录下的所有 cpp 文件
file(GLOB_RECURSE server_db_files "./db/*.cpp")


include_directories("${CMAKE_CURRENT_LIST_DIR}/mq")
file(GLOB_RECURSE server_mq_files "./mq/*.cpp")

add_library(server_mq_lib ${server_mq_files})

target_link_libraries(server_mq_lib PUBLIC rdkafka++ rdkafka pthread)

add_subdirectory(rpc)
add_subdirectory(rpcclient)
add_subdirectory(transfer)
add_subdirectory(push)
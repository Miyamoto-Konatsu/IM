
# 包含 gRPC 的头文件目录
include_directories(${gRPC_INCLUDE_DIRS})

# 包含 protobuf 生成的头文件目录，生成对应链接库
foreach(_target
    auth
    msg
    group
    conversation
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
file(GLOB_RECURSE server_db_files "${CMAKE_CURRENT_LIST_DIR}/db/*.c*")
add_library(server_db_lib ${server_db_files})
target_include_directories(server_db_lib PUBLIC  "/usr/local/include")
link_directories("/usr/local/lib")
target_link_libraries(server_db_lib PUBLIC odb odb-mysql odb cpp_redis tacopie)


include_directories("${CMAKE_CURRENT_LIST_DIR}/mq")
file(GLOB_RECURSE server_mq_files "./mq/*.cpp")
add_library(server_mq_lib ${server_mq_files})
target_include_directories(server_mq_lib PUBLIC  "/usr/local/include")
target_link_libraries(server_mq_lib PUBLIC rdkafka++ rdkafka pthread)

include_directories("${CMAKE_CURRENT_LIST_DIR}/common")
file(GLOB_RECURSE server_common_files "./common/*.cpp")
add_library(server_common_lib ${server_common_files})
target_include_directories(server_common_lib PUBLIC  "/usr/local/include")
target_link_libraries(server_common_lib pthread)


add_subdirectory(rpc)
add_subdirectory(rpcclient)
add_subdirectory(transfer)
add_subdirectory(push)
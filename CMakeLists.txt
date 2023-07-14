
cmake_minimum_required(VERSION 3.6.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules)

include_directories("/root/code/lib/include")
include_directories("/root/code/lib/include/google")
link_directories("/root/code/lib/lib")

set(Protoc_DIR "/root/code/lib/bin")

# 查找 protobuf
find_package(Protobuf REQUIRED HINTS "/root/code/lib")
# 查找 gRPC
find_package(gRPC REQUIRED)

add_subdirectory(src/server)



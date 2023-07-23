
cmake_minimum_required(VERSION 3.6.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules)

include_directories("/root/code/lib/include")
include_directories("/root/code/lib/include/google")
link_directories("/root/code/lib/lib")

# 查找 protobuf
find_package(Protobuf REQUIRED HINTS "/root/code/lib")
# 查找 gRPC
find_package(gRPC REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 获取配置文件的绝对路径
set(config_file_path "${CMAKE_CURRENT_LIST_DIR}/config/config.yaml")

# 定义一个宏，将文件路径作为宏的值传递给代码
add_compile_definitions(CONFIG_FILE_PATH="${config_file_path}")

add_subdirectory(src/server)



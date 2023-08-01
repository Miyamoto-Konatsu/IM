project(client)
file(GLOB_RECURSE client_src *.cpp )
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_executable(client ${client_src})

target_link_libraries(client muduo_net muduo_base pthread)
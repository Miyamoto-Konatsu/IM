include_directories(CMAKE_CURRENT_LIST_DIR)
file(GLOB_RECURSE gateway_files *.cpp)
add_executable(gate ${gateway_files})
target_link_libraries(gate muduo_net muduo_base pthread)
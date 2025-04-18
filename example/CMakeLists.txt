cmake_minimum_required(VERSION 3.20)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

add_executable(tree_example tree_example.cpp)
target_include_directories(tree_example PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(interval_map_example interval_map_example.cpp)
target_include_directories(interval_map_example PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(float_interval_map_example float_interval_map_example.cpp)
target_include_directories(float_interval_map_example PUBLIC ${CMAKE_SOURCE_DIR}/src)

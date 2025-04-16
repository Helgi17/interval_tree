cmake_minimum_required(VERSION 3.20)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

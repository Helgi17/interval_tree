cmake_minimum_required(VERSION 3.20)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

enable_testing()
add_executable(check basic.cpp)
target_include_directories(check PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(check gtest gtest_main)
add_test(NAME test COMMAND $<TARGET_FILE:check>)
# Показать include-пути для check
get_target_property(check_includes check INCLUDE_DIRECTORIES)
message("Check include paths: ${check_includes}")

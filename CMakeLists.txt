cmake_minimum_required(VERSION 3.10)
project(circular_buffer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)

add_executable(main main.cpp)

add_executable(tests tests.cpp)
target_link_libraries(tests gtest gtest_main)
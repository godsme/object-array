cmake_minimum_required(VERSION 3.19)
project(object_array)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party"
)

add_executable(object_array_test test/ut/catch.cpp)
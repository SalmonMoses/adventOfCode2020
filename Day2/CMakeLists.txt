cmake_minimum_required(VERSION 3.17)
project(Day2)

set(CMAKE_CXX_STANDARD 14)

FILE(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Day2 main.cpp)
cmake_minimum_required(VERSION 3.19)
project(prog)

set(CMAKE_CXX_STANDARD 14)

add_executable(prog main.cpp Date.cpp Date.h tests.cpp)
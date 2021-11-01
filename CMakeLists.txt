cmake_minimum_required(VERSION 3.19)
project(prog2)

set(CMAKE_CXX_STANDARD 14)

add_executable(prog2 main.cpp Date.cpp Date.h tests.cpp TimeString.h Event.h Event.cpp)
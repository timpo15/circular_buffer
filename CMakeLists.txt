cmake_minimum_required(VERSION 3.10)
project(Circular_buffer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -fsanitize=address")
add_executable(Circular_buffer main.cpp Circular_buffer.h)

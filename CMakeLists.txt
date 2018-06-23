cmake_minimum_required(VERSION 3.10)
project(Circular_buffer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -fsanitize=address,undefined,return --std=c++17")
add_executable(Circular_buffer_simple main.cpp Circular_buffer.h)
add_executable(Circular_buffer_hard testing.cpp
        Circular_buffer.h
        gtest/gtest.h gtest/gtest-all.cc gtest/gtest_main.cc
        counted.cpp counted.h fault_injection.cpp fault_injection.h)
target_link_libraries(Circular_buffer_hard -lpthread)

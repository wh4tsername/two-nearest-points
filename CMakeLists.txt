cmake_minimum_required(VERSION 3.15)
project(two_nearest_points)

set(CMAKE_CXX_STANDARD 20)

add_executable(two_nearest_points main.cpp)
add_executable(tester tester/tester.cpp)
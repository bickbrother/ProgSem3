cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 14)

project(ProgSem3)
include_directories(libs)
add_subdirectory(libs)

add_executable(ProgSem3 main.cpp)
add_subdirectory(Google_tests)

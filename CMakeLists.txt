cmake_minimum_required(VERSION 3.10)

project(accel-macros CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

add_library(accel-macros INTERFACE)
target_include_directories(accel-macros INTERFACE "include/")
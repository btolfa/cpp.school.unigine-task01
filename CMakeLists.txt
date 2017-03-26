cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(task01 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

add_executable(task01 main.cpp myvector.hpp catch.hpp)

cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(task01 CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

add_executable(task01
  myvector.hpp
  vector_interface.cpp
  gtest/gtest.h
  gtest/gtest-all.cc
  gtest/gtest_main.cc
)

target_include_directories(task01 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_directory_properties(VS_STARTUP_PROJECT task01)

add_test(NAME myvector COMMAND task01 --gtest_output=xml)

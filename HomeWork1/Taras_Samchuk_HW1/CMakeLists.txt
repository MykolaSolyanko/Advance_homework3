cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "clang++")

add_compile_options(
  -Wall 
  -Wextra 
  -Wpedantic 
  -Werror 
  -O3
  ) 

set(CMAKE_CXX_STANDARD 17)

project(HomeWork1)


set (CPP_FILES 
  main.cpp
  )

add_executable(${PROJECT_NAME} ${CPP_FILES})

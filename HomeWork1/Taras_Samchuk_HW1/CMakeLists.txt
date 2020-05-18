cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

add_compile_options(
  -Wall 
  -std=c++17
  -Wextra 
  -Wpedantic 
  -Werror 
  -O3
  ) 

project(HomeWork1)


set (CPP_FILES 
  main.cpp
  )

set (HPP_FILES
  vektor.hpp
  stek.hpp
  )


add_executable(HomeWork1 ${CPP_FILES} ${HPP_FILES})

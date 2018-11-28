cmake_minimum_required(VERSION 3.12)
project(Labo06)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic")

set(CMAKE_CXX_STANDARD 11)

add_executable(Labo06 main.cpp)
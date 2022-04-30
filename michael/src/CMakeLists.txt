cmake_minimum_required(VERSION 3.10)
project(AdventOfCode VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES
    ../include/*.h
    ../src/*.cpp)

add_executable(AdventOfCode ${SOURCES})

include_directories(../include)

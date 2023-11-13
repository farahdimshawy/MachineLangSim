cmake_minimum_required(VERSION 3.26)
project(machinesimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(machinesimulator main.cpp
        Machine.h
        memory.h
        memory.cpp
        Machine.cpp)

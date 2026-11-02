cmake_minimum_required(VERSION 4.1)
project(Volemachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(Volemachine main.cpp
        InputOutput.cpp
        InputOutput.h
        Loader.h
        Loader.cpp)

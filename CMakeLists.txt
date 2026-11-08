cmake_minimum_required(VERSION 4.1)
project(Volemachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(Volemachine main.cpp
        Machine.cpp
        Machine.h
        InputOutput.cpp
        InputOutput.h
        Loader.h
        Loader.cpp
        CPU.h
        Instruction.cpp
        Instruction.h
        Memory.h
        Memory.cpp
        Register.cpp
        Register.h
        CPU.cpp
        Machine.h
        Machine.cpp
        veryHardtest.txt)

configure_file(${CMAKE_SOURCE_DIR}/veryHardtest.txt ${CMAKE_BINARY_DIR}/veryHardtest.txt COPYONLY)
cmake_minimum_required(VERSION 3.19)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(Matrix

        Headers/Matrix.h
        Source/Matrix.cpp

        main.cpp)
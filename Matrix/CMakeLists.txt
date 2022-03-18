cmake_minimum_required(VERSION 3.19)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES    main.cpp
                    Source/Matrix.cpp)

set(HEADERS_FILES   Headers/Matrix.h)

add_executable(Matrix ${SOURCE_FILES} ${HEADERS_FILES})
cmake_minimum_required(VERSION 3.17)
project(NumbersLaba)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES source/methods.cpp source/structs.cpp)

add_executable(main main.cpp ${SOURCE_FILES})

include_directories(source)
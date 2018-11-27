cmake_minimum_required(VERSION 3.7)
project(Euler-Operations)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit")

set(SOURCE_FILES src/main.cpp src/TopologicalOperation.h src/TopologicalOperation.cpp)

add_executable(Euler-Operations ${SOURCE_FILES})


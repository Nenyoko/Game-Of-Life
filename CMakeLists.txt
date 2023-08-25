cmake_minimum_required(VERSION 3.26)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 23)
add_subdirectory(raylib)

add_executable(GameOfLife src/main.cpp
        src/grid.cpp
        src/grid.h)
target_link_libraries(GameOfLife raylib)

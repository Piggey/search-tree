cmake_minimum_required(VERSION 3.21)
project(search_tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

add_executable(${PROJECT_NAME}
        src/main.cpp
        inc/Tree.h src/Tree.cpp
)

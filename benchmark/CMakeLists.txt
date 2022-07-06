cmake_minimum_required(VERSION 3.21)
project(search_tree_benchmark)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-O2 -Wall -Wextra -pedantic -Werror)
endif()

include_directories(../inc)
add_executable(${PROJECT_NAME} benchmark.cpp)

target_link_libraries(${PROJECT_NAME} search_tree)
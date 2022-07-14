cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 14)
project(libsearch-tree
    DESCRIPTION "A tree data structure optimized for searching words given a prefix."
    VERSION 1.1.0
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/Piggey/search-tree
)

set(BUILD_TESTS OFF)

set(SEARCH_TREE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/search-tree)
set(SEARCH_TREE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SEARCH_TREE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(SEARCH_TREE_HEADERS_DIR ${PROJECT_SOURCE_DIR}/search-tree)

include_directories(${SEARCH_TREE_INSTALL_INCLUDE_DIR})
include_directories(${SEARCH_TREE_HEADERS_DIR})

# set compiler options
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-std=c++14 -O3 -Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(search-tree)
add_subdirectory(test)
add_subdirectory(benchmark)
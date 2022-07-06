cmake_minimum_required(VERSION 3.21)
project(search_tree VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(inc)
include_directories(lib)

add_library(${PROJECT_NAME}
        inc/search-tree/Tree.h src/Tree.cpp
        )

## LIBRARIES ##
include(FetchContent)

## gtest for testing
enable_testing()
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# create test executable
# there's probably a way better to do this than just compiling it again
add_executable(${PROJECT_NAME}_test
        test/treenode_test.cpp
        test/tree_test.cpp
)

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_test gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
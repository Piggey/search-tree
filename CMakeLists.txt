cmake_minimum_required(VERSION 3.21)
project(search_tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

add_executable(${PROJECT_NAME}
        src/main.cpp
        inc/Tree.h src/Tree.cpp
        inc/TreeNode.h
        inc/logger.h
)

## TESTS ##
enable_testing()

# GoogleTest library
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# create test executable
# there's probably a way better to do this than just compiling it again
add_executable(${PROJECT_NAME}_test
        test/treenode_test.cpp
        test/tree_test.cpp
        inc/Tree.h src/Tree.cpp
        inc/TreeNode.h
)

target_link_libraries(${PROJECT_NAME}_test gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
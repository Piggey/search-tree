cmake_minimum_required(VERSION 3.21)
project(search_tree_test)

include_directories(${SEARCH_TREE_HEADERS_DIR})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# create test executable
# there's probably a way better to do this than just compiling it again
add_executable(${PROJECT_NAME}
    treenode_test.cpp
    tree_test.cpp
)

target_link_libraries(${PROJECT_NAME} gtest_main)
target_link_libraries(${PROJECT_NAME} search_tree)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

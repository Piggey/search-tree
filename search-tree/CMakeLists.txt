cmake_minimum_required(VERSION 3.21)

project(search-tree)

set(SOURCE_FILES
        Tree.h Tree.cpp
        TreeNode.h
)

add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${SEARCH_TREE_INSTALL_LIB_DIR})
install(FILES Tree.h DESTINATION ${SEARCH_TREE_INSTALL_INCLUDE_DIR})
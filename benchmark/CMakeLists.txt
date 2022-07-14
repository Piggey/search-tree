cmake_minimum_required(VERSION 3.21)
project(search-tree-benchmark)

include_directories(${SEARCH_TREE_INSTALL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} benchmark.cpp)
target_link_libraries(${PROJECT_NAME} search-tree)

install(TARGETS ${PROJECT_NAME} DESTINATION ${SEARCH_TREE_INSTALL_BIN_DIR})
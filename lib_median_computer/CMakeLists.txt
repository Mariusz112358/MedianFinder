cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

project(lib_median_computer)
add_subdirectory(heap_median)
add_subdirectory(tree_median)
aux_source_directory(. SRC_LIST)
aux_source_directory(./heap_median SRC_LIST)
aux_source_directory(./tree_median SRC_LIST)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})


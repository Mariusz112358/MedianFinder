cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

project(tree_median)
aux_source_directory(. SRC_LIST)
aux_source_directory(./heap_median SRC_LIST)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})


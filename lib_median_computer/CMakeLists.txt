cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++14)

project(lib_median_computer)
aux_source_directory(. SRC_LIST)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})


cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

project(rand_tests)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

include_directories(${lib_median_computer_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} lib_median_computer)

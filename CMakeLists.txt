cmake_minimum_required(VERSION 3.0)

project(SOLDIERFIRE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(src/ SRC_LISTS)

add_executable(test_exe main.cpp ${SRC_LISTS})
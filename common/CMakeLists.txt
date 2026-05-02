cmake_minimum_required(VERSION 3.10)
project(common LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(common SHARED src/common.cpp)

target_include_directories(common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(common PROPERTIES
    OUTPUT_NAME "common"
    POSITION_INDEPENDENT_CODE ON
)

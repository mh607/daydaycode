cmake_minimum_required(VERSION 3.0)

project(TEST)

# 查找zlib库
find_package(ZLIB REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include /usr/include)

# 添加子目录
add_subdirectory(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_BUILD_TYPE Debug)

add_executable(test_exe main.cpp)

target_link_libraries(test_exe my_library ZLIB::ZLIB)
cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17 -lfreeimage)

set(CXX_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(Capstone)

find_path(SIFTGPU_INCLUDE_DIR FreeImage.h)
find_library(SIFTGPU_LIBRARY libfreeimage)
include_directories(${SIFTGPU_INCLUDE_DIR})

add_executable(Capstone src/main.cpp src/saveimage.cpp)

target_link_libraries(Capstone freeimage)
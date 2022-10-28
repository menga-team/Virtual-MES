cmake_minimum_required(VERSION 3.20)

project(vmes)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(vmes main.cpp)
target_link_libraries(vmes ${SDL2_LIBRARIES})
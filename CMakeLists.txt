cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

# https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(vmes)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(vmes main.cpp)
target_link_libraries(vmes ${SDL2_LIBRARIES})
target_link_libraries(vmes ${SDL2_IMAGE_LIBRARIES})
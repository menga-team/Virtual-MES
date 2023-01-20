cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)

# https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(vmes)

find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
# include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(src)

add_executable(examplec examples/movement/src/main.c src/vmes.c src/gpu.c src/controller.c src/timer.c src/gpu.h src/gpu_internal.h src/controller.h src/controller_internal.h src/timer.h examples/movement/include/mesmath.h examples/movement/include/mesgraphics.h)
target_link_libraries(examplec ${SDL2_LIBRARIES})
target_link_libraries(examplec ${SDL2_IMAGE_LIBRARIES})

#add_executable(cubec examples/cube/cube.c src/gpu.c src/controller.c src/timer.c examples/movement/include/mesmath.h examples/movement/include/mesgraphics.h examples/movement/include/mesmath.h)
#target_link_libraries(cubec ${SDL2_LIBRARIES})
#target_link_libraries(cubec ${SDL2_IMAGE_LIBRARIES})
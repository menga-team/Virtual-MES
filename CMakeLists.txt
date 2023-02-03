cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)

project(vmes)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(src)

add_executable(movement examples/movement/src/main.c src/vmes.c src/gpu.c src/controller.c src/timer.c src/gpu.h src/gpu_internal.h src/controller.h src/controller_internal.h src/timer.h examples/movement/include/mesmath.h examples/movement/include/mesgraphics.h)
target_link_libraries(movement ${SDL2_LIBRARIES})
target_link_libraries(movement m)

add_executable(debug examples/debug/src/main.c src/vmes.c src/gpu.c src/controller.c src/timer.c src/gpu.h src/gpu_internal.h src/controller.h src/controller_internal.h src/timer.h)
target_link_libraries(debug ${SDL2_LIBRARIES})
target_link_libraries(debug m)

add_executable(cube examples/cube/src/main.c src/vmes.c src/gpu.c src/controller.c src/timer.c src/gpu.h src/gpu_internal.h src/controller.h src/controller_internal.h src/timer.h examples/cube/include/mesmath.h examples/cube/include/mesgraphics.h)
target_link_libraries(cube ${SDL2_LIBRARIES})
target_link_libraries(cube m)

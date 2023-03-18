cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)

project(vmes)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include)
set(VMES_SOURCES src/vmes.c src/gpu.c src/controller.c src/timer.c)

file(GLOB SOURCES_MOVEMENT "examples/movement/src/*.c")
add_executable(movement ${SOURCES_MOVEMENT} ${VMES_SOURCES})
target_link_libraries(movement ${SDL2_LIBRARIES})
target_link_libraries(movement m)

file(GLOB SOURCES_DEBUG "examples/debug/src/*.c")
add_executable(debug ${SOURCES_DEBUG} src/vmes.c src/gpu.c src/controller.c src/timer.c include/gpu.h include/gpu_internal.h include/controller.h include/controller_internal.h include/timer.h)
target_link_libraries(debug ${SDL2_LIBRARIES})
target_link_libraries(debug m)

file(GLOB SOURCES_DEBUG "examples/debug/src/*.c")
add_executable(cube examples/cube/src/main.c src/vmes.c src/gpu.c src/controller.c src/timer.c include/gpu.h include/gpu_internal.h include/controller.h include/controller_internal.h include/timer.h examples/cube/include/mesmath.h examples/cube/include/mesgraphics.h)
target_link_libraries(cube ${SDL2_LIBRARIES})
target_link_libraries(cube m)

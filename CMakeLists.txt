cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)

project(vmes)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include)
set(SOURCES_VMES src/vmes.c src/gpu.c src/input.c src/timer.c)

file(GLOB SOURCES_MOVEMENT "examples/movement/src/*.c")
add_executable(movement ${SOURCES_MOVEMENT} ${SOURCES_VMES})
target_link_libraries(movement ${SDL2_LIBRARIES})
target_link_libraries(movement m)

file(GLOB SOURCES_DEBUG "examples/debug/src/*.c")
add_executable(debug ${SOURCES_DEBUG} ${SOURCES_VMES})
target_link_libraries(debug ${SDL2_LIBRARIES})
target_link_libraries(debug m)

file(GLOB SOURCES_CUBE "examples/cube/src/*.c")
add_executable(cube ${SOURCES_CUBE} ${SOURCES_VMES})
target_link_libraries(cube ${SDL2_LIBRARIES})
target_link_libraries(cube m)

file(GLOB SOURCES_HELLOWORLD "examples/helloworld/src/*.c")
add_executable(helloworld ${SOURCES_HELLOWORLD} ${SOURCES_VMES})
target_link_libraries(helloworld ${SDL2_LIBRARIES})
target_link_libraries(helloworld m)
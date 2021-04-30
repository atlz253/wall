cmake_minimum_required(VERSION 3.16.3)

project(wall VERSION 250421)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(SDLWINDOW STATIC src/graphic.cpp)
target_link_libraries(SDLWINDOW ${SDL2_LIBRARIES})

add_executable(MAIN src/main.cpp)
target_link_libraries(MAIN SDLWINDOW)
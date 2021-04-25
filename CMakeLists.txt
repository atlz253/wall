cmake_minimum_required(VERSION 3.16.3)

project(wall VERSION 250421)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(main src/main.cpp)
target_link_libraries(main ${SDL2_LIBRARIES})
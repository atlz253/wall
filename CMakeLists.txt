cmake_minimum_required(VERSION 3.16.3)

project(wall VERSION 010521)

# set(CMAKE_BUILD_TYPE Debug)

# include_directories("${PROJECT_SOURCE_DIR}/src")
# include_directories("${PROJECT_SOURCE_DIR}/src/logger")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(LOGGER STATIC src/logger/logger.cpp)

add_library(SDLWINDOW STATIC src/graphic.cpp)
target_link_libraries(SDLWINDOW ${SDL2_LIBRARIES} LOGGER)

add_executable(MAIN src/main.cpp)
target_link_libraries(MAIN SDLWINDOW LOGGER)
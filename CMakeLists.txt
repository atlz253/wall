#
# Project settings
#
cmake_minimum_required(VERSION 3.16)
project(wall VERSION 030721)

#
# Libraries check
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/.cmake/FindSDL2")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
)

#
# Include subprojects
#
add_subdirectory(engine)
include_directories("${PROJECT_SOURCE_DIR}/engine/include")

#
# Include dirs
#
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

include_directories(
    "${SRC_DIR}/event"
    "${SRC_DIR}/menu"
    "${SRC_DIR}/object"
    "${SRC_DIR}/units"
    "${SRC_DIR}/video"
    "${SRC_DIR}/wall"
    "${SRC_DIR}/world"
)

#
# Add files
#
set(
    CPP_FILES 
    ${SRC_DIR}/event/eventSubSystem.cpp
    ${SRC_DIR}/menu/button.cpp
    ${SRC_DIR}/menu/input.cpp
    ${SRC_DIR}/object/text.cpp
    ${SRC_DIR}/units/base.cpp
    ${SRC_DIR}/units/knight.cpp
    ${SRC_DIR}/units/unit.cpp
    ${SRC_DIR}/wall/globals.cpp
    ${SRC_DIR}/wall/print.cpp
    ${SRC_DIR}/wall/random.cpp
    ${SRC_DIR}/wall/wall.cpp
    ${SRC_DIR}/world/action.cpp
    ${SRC_DIR}/world/background.cpp
    ${SRC_DIR}/world/gui.cpp
    ${SRC_DIR}/world/terrain.cpp
    ${SRC_DIR}/main.cpp
)

set(
    HPP_FILES 
    ${SRC_DIR}/event/eventSubSystem.hpp
    ${SRC_DIR}/menu/button.hpp
    ${SRC_DIR}/menu/input.hpp
    ${SRC_DIR}/object/text.hpp
    ${SRC_DIR}/units/base.hpp
    ${SRC_DIR}/units/knight.hpp
    ${SRC_DIR}/units/unit.hpp
    ${SRC_DIR}/wall/globals.hpp
    ${SRC_DIR}/wall/print.hpp
    ${SRC_DIR}/wall/random.hpp
    ${SRC_DIR}/wall/wall.hpp
    ${SRC_DIR}/world/action.hpp
    ${SRC_DIR}/world/background.hpp
    ${SRC_DIR}/world/gui.hpp
    ${SRC_DIR}/world/terrain.hpp
)

#
# Create executable
#
add_executable(wall ${HPP_FILES} ${CPP_FILES})

target_link_libraries(
    wall 
    engine 
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
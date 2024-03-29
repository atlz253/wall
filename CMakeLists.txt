#
# Project settings
#
cmake_minimum_required(VERSION 3.16)
project(wall VERSION 150721)

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
    ${SRC_DIR}/units/base.cpp
    ${SRC_DIR}/units/knight.cpp
    ${SRC_DIR}/units/unit.cpp
    ${SRC_DIR}/wall/globals.cpp
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
    ${SRC_DIR}/units/base.hpp
    ${SRC_DIR}/units/knight.hpp
    ${SRC_DIR}/units/unit.hpp
    ${SRC_DIR}/wall/globals.hpp
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
)
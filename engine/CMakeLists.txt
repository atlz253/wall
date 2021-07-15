#
# Project settings
#
cmake_minimum_required(VERSION 3.16)
project(engine VERSION 150721)

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
# Include dirs
#
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories(
    "${INCLUDE_DIR}"
    "${SRC_DIR}"
    "${SRC_DIR}/objects"
)

#
# Add files
#
set(
    CPP_FILES
    ${SRC_DIR}/input/keyboard.cpp
    ${SRC_DIR}/input/mouse.cpp
    ${SRC_DIR}/menu/button.cpp
    ${SRC_DIR}/objects/entity.cpp
    ${SRC_DIR}/objects/layer.cpp
    ${SRC_DIR}/objects/text.cpp
    ${SRC_DIR}/objects/textureManager.cpp
    ${SRC_DIR}/engine.cpp
    ${SRC_DIR}/event.cpp
    ${SRC_DIR}/global.cpp
)

set(
    HPP_FILES
    ${INCLUDE_DIR}/engine.hpp
    ${INCLUDE_DIR}/entity.hpp
    ${INCLUDE_DIR}/event.hpp
    ${INCLUDE_DIR}/interface.hpp
    ${INCLUDE_DIR}/layer.hpp
    ${INCLUDE_DIR}/type.hpp
    ${SRC_DIR}/objects/textureManager.hpp
    ${SRC_DIR}/global.hpp
)

#
# Create library
#
add_library(
    engine 
    ${HPP_FILES} 
    ${CPP_FILES}
)

target_link_libraries(
    engine 
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
#
# Project settings
#
cmake_minimum_required(VERSION 3.16)
project(engine VERSION 130721)

#
# Include dirs
#
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories(
    "${INCLUDE_DIR}"
    "${SRC_DIR}"
)

#
# Add files
#
set(
    CPP_FILES
    ${SRC_DIR}/menu/button.cpp
    ${SRC_DIR}/objects/entity.cpp
    ${SRC_DIR}/objects/layer.cpp
    ${SRC_DIR}/objects/rotateEntity.cpp
    ${SRC_DIR}/objects/text.cpp
    ${SRC_DIR}/objects/textureManager.cpp
    ${SRC_DIR}/engine.cpp
    ${SRC_DIR}/global.cpp
)

set(
    HPP_FILES
    ${INCLUDE_DIR}/button.hpp
    ${INCLUDE_DIR}/engine.hpp
    ${INCLUDE_DIR}/entity.hpp
    ${INCLUDE_DIR}/layer.hpp
    ${INCLUDE_DIR}/text.hpp
    ${INCLUDE_DIR}/textureManager.hpp
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
    engine ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
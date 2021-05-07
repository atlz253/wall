cmake_minimum_required(VERSION 3.16.3)

# настройки проекта
project(wall VERSION 060521)
# set(CMAKE_BUILD_TYPE Debug)

# путь до модулей cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# подключение SDL2
find_package(SDL2 REQUIRED)

# подключение SDL2_image
find_package(SDL2_image REQUIRED)

# библиотека основных компонентов
add_library(WALL STATIC 
                        src/object/entity.cpp
                        src/object/texture.cpp
                        src/video/renderer.cpp
                        src/video/window.cpp
                        src/wall/main.cpp
                        src/wall/print.cpp)
target_link_libraries(WALL SDL2::Core SDL2::Image)
target_include_directories(WALL 
                                PUBLIC "${PROJECT_SOURCE_DIR}/src/object"
                                PUBLIC "${PROJECT_SOURCE_DIR}/src/video"
                                PUBLIC "${PROJECT_SOURCE_DIR}/src/wall")

# сборка исполняемого файла
add_executable(MAIN src/main.cpp)
target_link_libraries(MAIN WALL)
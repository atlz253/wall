cmake_minimum_required(VERSION 3.16.3)

# настройки проекта
project(wall VERSION 030521)
# set(CMAKE_BUILD_TYPE Debug)

# путь до модулей cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# подключение SDL2
find_package(SDL2 REQUIRED)

# подключение SDL2_image
find_package(SDL2_image REQUIRED)

# библиотека основных компонентов
add_library(WALL STATIC 
                        src/wall/main.cpp
                        src/video/window.cpp
                        src/video/resources.cpp
                        src/logger/logger.cpp)
target_link_libraries(WALL SDL2::Core SDL2::Image)
target_include_directories(WALL 
                                PUBLIC "${PROJECT_SOURCE_DIR}/src/wall"
                                PUBLIC "${PROJECT_SOURCE_DIR}/src/video"
                                PUBLIC "${PROJECT_SOURCE_DIR}/src/logger")

# сборка исполняемого файла
add_executable(MAIN src/main.cpp)
target_link_libraries(MAIN WALL)
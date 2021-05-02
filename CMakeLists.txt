cmake_minimum_required(VERSION 3.16.3)

# настройки проекта
project(wall VERSION 020521)
# set(CMAKE_BUILD_TYPE Debug)

# путь до модулей cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# подключение SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# подключение SDL2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_DIRS})

# директории для поиска заголовочных файлов
include_directories("${PROJECT_SOURCE_DIR}/src")    

# библиотека логгирования
add_library(LOGGER STATIC src/logger/logger.cpp)
include_directories("${PROJECT_SOURCE_DIR}/src/logger")

add_library(SDLWINDOW STATIC src/graphic.cpp)
target_link_libraries(SDLWINDOW SDL2::Core SDL2::Image LOGGER)

add_executable(MAIN src/main.cpp)
target_link_libraries(MAIN SDLWINDOW LOGGER)
cmake_minimum_required(VERSION 3.16.3)

# настройки проекта
project(wall VERSION 030521)
# set(CMAKE_BUILD_TYPE Debug)

# путь до модулей cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# подключение SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# подключение SDL2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_DIRS})  

# библиотека логгирования
add_library(LOGGER STATIC src/logger/logger.cpp)
target_include_directories(LOGGER PUBLIC "${PROJECT_SOURCE_DIR}/src/logger")

# библиотеа графики
set(VIDEO_DIR src/video)
add_library(SDLWINDOW STATIC ${VIDEO_DIR}/window.cpp ${VIDEO_DIR}/resources.cpp)
target_link_libraries(SDLWINDOW SDL2::Core SDL2::Image LOGGER)
target_include_directories(SDLWINDOW PUBLIC "${PROJECT_SOURCE_DIR}/${VIDEO_DIR}")

# библиотека основных компонентов
set(WALL_DIR src/wall)
add_library(WALL STATIC ${WALL_DIR}/main.cpp)
target_link_libraries(WALL SDLWINDOW LOGGER)
target_include_directories(SDLWINDOW PUBLIC "${PROJECT_SOURCE_DIR}/${WALL_DIR}")

# сборка исполняемого файла
add_executable(MAIN src/main.cpp)
target_link_libraries(MAIN WALL)
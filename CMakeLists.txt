cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Locate GLEW and GLFW
find_package(GLEW REQUIRED)
find_package(glfw REQUIRED)

add_subdirectory(src)

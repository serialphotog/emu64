cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Locate GLEW and GLFW
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# GLFW
add_subdirectory(extern/glfw)
include_directories(extern/glfw/include)

# The emulation library
add_subdirectory(libemu64)

# The frontend
add_subdirectory(src)

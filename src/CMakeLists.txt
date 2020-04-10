project("emu64" VERSION 0.0.1 LANGUAGES CXX)

set(EMU_SRCS
	main.cpp
)
include_directories(.)

add_executable(${PROJECT_NAME} ${EMU_SRCS})
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW glfw)
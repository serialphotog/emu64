project("emu64" VERSION 0.0.1 LANGUAGES CXX)

set(EMU_SRCS
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_widgets.cpp
	imgui/imgui.cpp 
	ui/emulator_window.cpp
	ui/file_browser.cpp
	ui/imgui_impl_glfw.cpp
	ui/imgui_impl_opengl3.cpp
	emu.cpp
	main.cpp
)
include_directories(.)

add_executable(${PROJECT_NAME} ${EMU_SRCS})
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW glfw libemu64)
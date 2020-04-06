project("emu64" C)

set(EMU_SRCS
	main.c
	util/byteutils.c
	sys/sys.c
	sys/cpu/cp0/cp0.c
	sys/cpu/cp1/cp1.c
	sys/cpu/cpustate.c
	sys/cpu/cpu.c
	sys/memory.c
	sys/pif.c
)
include_directories(.)
include_directories(${GLFW_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${EMU_SRCS})
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW ${GLFW_LIBRARY})
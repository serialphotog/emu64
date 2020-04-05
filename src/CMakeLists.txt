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

add_executable(${PROJECT_NAME} ${EMU_SRCS})

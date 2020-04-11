project("libemu64" VERSION 0.0.1 LANGUAGES CXX C)

set (LIB_EMU64_SRCS
    system.cpp
    pif.cpp
    memory.cpp
    memory_section.cpp
    rom.cpp
    util/byteutils.c
    sys/memory.c
    sys/cpu/cpu.c 
    sys/cpu/cpustate.c 
    sys/cpu/cp0/cp0.c 
    sys/cpu/cp1/cp1.c 
)
add_library(${PROJECT_NAME} STATIC ${LIB_EMU64_SRCS})
target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR} 
)
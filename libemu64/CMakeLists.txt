project("libemu64" VERSION 0.0.1 LANGUAGES CXX C)

set (LIB_EMU64_SRCS
    system.cpp
    pif.cpp
    memory.cpp
    memory_section.cpp
    rom.cpp
    vr4300/processor.cpp
    vr4300/cp0.cpp
    vr4300/processor_state.cpp
    vr4300/register.cpp
    vr4300/instruction.cpp
    vr4300/cpu.cpp
)
add_library(${PROJECT_NAME} STATIC ${LIB_EMU64_SRCS})
target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR} 
)
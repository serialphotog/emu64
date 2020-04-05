#ifndef __EMU_CPU_H__
#define __EMU_CPU_H__

#include "sys/cpu/cp0/cp0.h"
#include "sys/cpu/cp1/cp1.h"
#include "sys/cpu/cpustate.h"
#include "sys/memory.h"

// The primary structure for the CPU
typedef struct CPU {
    CP0* cp0; // The system coprocessor
    CP1* cp1; // The system FPU coprocessor
    CPUState* state; // Stores the current state of the CPU
} CPU;

// Represents an instruction within the system
typedef struct Instruction {
    uint32_t instruction; // The full instruction
    uint8_t opcode; // The opcode portion of the instruction
    uint8_t base;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd; 
    uint8_t sa;
    uint8_t function;
    uint16_t offset;
} Instruction;

// Creates a new CPU instance
CPU* cpu_create();

// Runs the CPU fetch-execute cycle
void cpu_run(CPU* cpu, Memory* memory);

// Executes a cpu instruction
void cpu_execute_instruction(CPU* cpu, Memory* memory, Instruction* instruction);

// Decodes an instruction
void cpu_decode_instruction(Instruction* instruction);

// Performs an instruction fetch
Instruction* cpu_fetch_instruction(Memory* memory, uint32_t addr);

// Performs cleanup
void cpu_destory(CPU* cpu);

#endif

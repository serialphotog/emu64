#include "sys/cpu/cpu.h"

#include "sys/cpu/opcodes.h"

#include <stdlib.h>
#include <stdio.h>

CPU* cpu_create() 
{
    CPU* cpu = calloc(1, sizeof(CPU));
    cpu->cp0 = cp0_create();
    cpu->cp1 = cp1_create();
    cpu->state = cpuState_create();

    return cpu;
}

void cpu_run(CPU* cpu, Memory* memory)
{
    while (1) // TODO: This shouldn't remain an infinite loop... 
    {
        Instruction* instruction = cpu_fetch_instruction(memory, cpu->state->pc);
        cpu_decode_instruction(instruction);
        cpu_execute_instruction(cpu, memory, instruction);
    }
}

Instruction* cpu_fetch_instruction(Memory* memory, uint32_t addr)
{
    Instruction* instruction = calloc(1, sizeof(Instruction));
    instruction->instruction = memory_read_word(memory, addr);
    return instruction;
}

void cpu_decode_instruction(Instruction* instruction)
{
    instruction->opcode = instruction->instruction >> 26;
    instruction->rs = instruction->base = (instruction->instruction >> 21) & 0x1f;
    instruction->rt = (instruction->instruction >> 16) & 0x1f;
    instruction->rd = (instruction->instruction >> 11) & 0x1f;
    instruction->sa = (instruction->instruction >> 6) & 0x1f;
    instruction->function = instruction->instruction & 0x3f;
    instruction->offset = instruction->instruction & 0xffff;
}

void cpu_destory(CPU* cpu)
{
    cp0_destroy(cpu->cp0);
    cp1_destroy(cpu->cp1);
    cpuState_destroy(cpu->state);
    free(cpu);
}

void cpu_execute_instruction(CPU* cpu, Memory* memory, Instruction* instruction)
{
    switch(instruction->opcode)
    {
        case OP_MFC0: // Identical to MTC0. Determined by value of rs
            if (instruction->rs == MFC0_RS_FLAG)
            {
                printf("Found MFC0. Implement me!\n");
                exit(1);
            }
            else if (instruction->rs == MTC0_RS_FLAG)
            {
               op_mtc0(cpu, instruction->rt, instruction->rd);
            }
            else 
            {
                printf("[CPU]: Unknown MFC0/MTC0 flag: %#02x\n", instruction->rs);
                exit(1);
            }
            break;
        default:
            printf("[CPU]: Unknown instruction: %#04x\n", instruction->opcode);
            exit(1);
            break;
    }
}

void op_mtc0(CPU* cpu, uint8_t rt, uint8_t rd)
{
    uint64_t* source = cpu_map_register(cpu->state, rt);
    uint64_t* dest = cp0_map_register(cpu->cp0, rd);
    *dest = *source;
}
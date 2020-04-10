#include "emu64/sys/cpu/cpu.h"

#include "emu64/emu64.h"
#include "emu64/sys/cpu/opcodes.h"

#include <stdlib.h>
#include <stdio.h>

CPU* cpu_create(EmuFlags* flags) 
{
    CPU* cpu = calloc(1, sizeof(CPU));
    cpu->cp0 = cp0_create();
    cpu->cp1 = cp1_create();
    cpu->state = cpuState_create();
    cpu->flags = flags;

    return cpu;
}

void cpu_run(CPU* cpu, Memory* memory)
{
    while (1)
    {
        Instruction* instruction = cpu_fetch_instruction(memory, cpu->state->pc);
        cpu_decode_instruction(instruction);
        cpu_execute_instruction(cpu, memory, instruction);

        if (cpu->flags->debugMode && cpu->flags->singleStepMode)
        {
            break;
        }
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
                // TOOD: Implement me
            }
            else if (instruction->rs == MTC0_RS_FLAG)
            {
               op_mtc0(cpu, instruction->rt, instruction->rd);
            }
            else 
            {
                printf("[CPU]: Unknown MFC0/MTC0 flag: %#02x\n", instruction->rs);
                // TODO: Implement me
            }
            break;
        case OP_LUI:
            op_lui(cpu, instruction->rt, instruction->offset);
            break;
        case OP_ADDIU:
           op_addiu(cpu, instruction->rs, instruction->rt, instruction->offset);
           break;
        default:
            printf("[CPU]: Unknown instruction: %#04x\n", instruction->opcode);
            break;
    }
}

void op_mtc0(CPU* cpu, uint8_t rt, uint8_t rd)
{
    uint64_t* source = cpu_map_register(cpu->state, rt);
    uint64_t* dest = cp0_map_register(cpu->cp0, rd);
    *dest = *source;
    cpu->state->pc += 4;
}

void op_lui(CPU* cpu, uint8_t rt, uint16_t imm)
{
    uint64_t* dest = cpu_map_register(cpu->state, rt);
    *dest = (uint64_t)(imm << 16);
    cpu->state->pc += 4;
}

void op_addiu(CPU* cpu, uint8_t rs, uint8_t rt, uint16_t imm)
{
    uint64_t* dest = cpu_map_register(cpu->state, rt);
    uint64_t* source = cpu_map_register(cpu->state, rs);
    *dest = source + (int16_t)imm;
    cpu->state->pc += 4;
}

const char* cpu_register_to_string(uint64_t val)
{
    if (val == NULL)
    {
        return "NULL";
    }
    else
    {
        char *result = malloc(11);
        snprintf(result, 11, "%#10x", val);
        return result;
    }
}
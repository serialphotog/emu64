#ifdef _WIN32 || _WIN64
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "sys/memory.h"
#include "util/byteutils.h"

#include <stdio.h>

#include "sys/cpu/cp0/cp0.h"

Memory* memory_create() 
{
    Memory* memory = calloc(1, sizeof(Memory));
    return memory;
}

void memory_destroy(Memory* memory)
{
    if (memory->rom != NULL) free(memory->rom);
    free(memory);
}

void memory_load_rom(Memory* memory, char* path)
{
    FILE *fp = fopen(path, "rb");
    if (fp == NULL)
    {
        printf("[ERROR]: Failed to load from %s\n", path);
        exit(1);
    }

    memory->rom = calloc(1, sizeof(Rom));
    
    fseek(fp, 0L, SEEK_END);
    memory->rom->sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    memory->rom->data = malloc(memory->rom->sz);
    fread(memory->rom->data, memory->rom->sz, 1, fp);

    fclose(fp);
}

MemorySection* memory_get_section(Memory* memory, uint32_t addr)
{
    MemorySection* section = calloc(1, sizeof(MemorySection));
    
    if ((addr >= RDRAM_BEGIN) && (addr <= RDRAM_END)) // RDRAM
    {
        section->offset = RDRAM_OFFSET;
        section->pointer = memory->rdram;
        return section;
    }

    if ((addr >= RDRAM_REGISTERS_BEGIN) && (addr <= RDRAM_REGISTERS_END)) // RDRAM Registers
    {
        section->offset = RDRAM_REGISTERS_OFFSET;
        section->pointer = memory->rdram_registers;
        return section;
    }

    if ((addr >= SP_DMEM_BEGIN) && (addr <= SP_DMEM_END)) // SP_DMEM
    {
        section->offset = SP_DMEM_OFFSET;
        section->pointer = memory->sp_dmem;
        return section;
    }

    if ((addr >= SP_IMEM_BEGIN) && (addr <= SP_IMEM_END)) // SP_IMEM
    {
        section->offset = SP_IMEM_OFFSET;
        section->pointer = memory->sp_imem;
        return section;
    }

    if ((addr >= SP_REGISTERS_BEGIN) && (addr <= SP_REGISTERS_END)) // SP_REGISTERS
    {
        section->offset = SP_REGISTERS_OFFSET;
        section->pointer = memory->sp_registers;
        return section;
    }

    if ((addr >= SP_REGISTERS_2_BEGIN) && (addr <= SP_REGISTERS_2_END)) // SP_REGISTERS2
    {
        section->offset = SP_REGISTERS_2_OFFSET;
        section->pointer = memory->sp_registers2;
        return section;
    }

    if ((addr >= DP_COMMAND_REGISTERS_BEGIN) && (addr <= DP_COMMAND_REGISTERS_END)) // DP_COMMAND_REGISTERS
    {
        section->offset = DP_COMMAND_REGISTERS_OFFSET;
        section->pointer = memory->dp_command_registers;
        return section;
    }

    if ((addr >= DP_SPAN_REGISTERS_BEGIN) && (addr <= DP_SPAN_REGISTERS_END)) // DP_SPAN_REGISTERS
    {
        section->offset = DP_SPAN_REGISTERS_OFFSET;
        section->pointer = memory->dp_span_registers;
        return section;
    }

    if ((addr >= MI_REGISTERS_BEGIN) && (addr <= MI_REGISTERS_END)) // MI_REGISTERS
    {
        section->offset = MI_REGISTERS_OFFSET;
        section->pointer = memory->mi_registers;
        return section;
    }

    if ((addr >= VI_REGISTERS_BEGIN) && (addr <= VI_REGISTERS_END)) // VI_REGISTERS
    {
        section->offset = VI_REGISTERS_OFFSET;
        section->pointer = memory->vi_registers;
        return section;
    }

    if ((addr >= AI_REGISTERS_BEGIN) && (addr <= AI_REGISTERS_END)) // AI_REGISTERS
    {
        section->offset = AI_REGISTERS_OFFSET;
        section->pointer = memory->ai_registers;
        return section;
    }

    if ((addr >= PI_REGISTERS_BEGIN) && (addr <= PI_REGISTERS_END)) // PI_REGISTERS
    {
        section->offset = PI_REGISTERS_OFFSET;
        section->pointer = memory->pi_registers;
        return section;
    }

    if ((addr >= RI_REGISTERS_BEGIN) && (addr <= RI_REGISTERS_END)) // RI_REGISTERS
    {
        section->offset = RI_REGISTERS_OFFSET;
        section->pointer = memory->ri_registers;
        return section;
    }

    if ((addr >= SI_REGISTERS_BEGIN) && (addr <= SI_REGISTERS_END)) // SI_REGISTERS
    {
        section->offset = SI_REGISTERS_OFFSET;
        section->pointer = memory->si_registers;
        return section;
    }

    if ((addr >= ROM_BEGIN) && (addr <= ROM_END)) // ROM
    {
        section->offset = ROM_OFFSET;
        if ((addr - section->offset) > memory->rom->sz)
        {
            // Illegal address
            printf("[ERROR]: Physical address 0x%#010x is out of bounds.\n", addr);
            exit(1);
        }
        section->pointer = memory->rom->data;
        return section;
    }
}

uint8_t memory_read_byte(Memory* memory, uint32_t addr)
{
    uint32_t phys_addr = addr & 0x1FFFFFFF;
    MemorySection* section = memory_get_section(memory, phys_addr);
    uint8_t* ptr = (uint8_t*)section->pointer;
    return ptr[phys_addr - section->offset];
}

void memory_write_byte(Memory* memory, uint32_t addr, uint8_t value)
{
    uint32_t phys_addr = addr & 0x1FFFFFFF;
    MemorySection* section = memory_get_section(memory, phys_addr);
    uint8_t* ptr = (uint8_t*)section->pointer;
    ptr[phys_addr - section->offset] = value;
}

uint16_t memory_read_hword(Memory* memory, uint32_t addr) 
{
    uint32_t phys_addr = addr & 0x1FFFFFFF;
    MemorySection* section = memory_get_section(memory, phys_addr);
    uint32_t pointer = phys_addr - section->offset;
    if (pointer) pointer /= 2;
    uint16_t* ptr = (uint16_t*)section->pointer;
    return ptr[pointer];
}

void memory_write_hword(Memory* memory, uint32_t addr, uint16_t value)
{
    uint32_t phys_addr = addr & 0x1FFFFFFF;
    MemorySection* section = memory_get_section(memory, phys_addr);
    uint32_t pointer = phys_addr - section->offset;
    if (pointer) pointer /= 2;
    uint16_t* ptr = (uint16_t*)section->pointer;
    ptr[pointer] = value;
}

uint32_t memory_read_word(Memory* memory, uint32_t addr)
{
    uint32_t phys_addr = addr & 0x1FFFFFFF;
    MemorySection* section = memory_get_section(memory, phys_addr);
    uint32_t pointer = phys_addr - section->offset;
    if (pointer) pointer /= 4;
    uint32_t* ptr = (uint32_t*)section->pointer;
    return bswap_32(ptr[pointer]);
}

void memory_write_word(Memory* memory, uint32_t addr, uint32_t value)
{
    uint32_t phys_addr = addr & 0x1FFFFFFF;
    MemorySection* section = memory_get_section(memory, phys_addr);
    uint32_t pointer = phys_addr - section->offset;
    if (pointer) pointer /= 4;
    uint32_t *ptr = (uint32_t*)section->pointer;
    ptr[pointer] = bswap_32(value);
}

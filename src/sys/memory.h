#ifndef __EMU_MEMORY_H__
#define __EMU_MEMORY_H__

#include <stdint.h>
#include <stdlib.h>

// Memory section limits
#define RDRAM_BEGIN 0x00000000
#define RDRAM_END 0x003FFFFF
#define RDRAM_REGISTERS_BEGIN 0x03F00000
#define RDRAM_REGISTERS_END 0x03FFFFFF
#define SP_DMEM_BEGIN 0x04000000
#define SP_DMEM_END 0x04000FFF
#define SP_IMEM_BEGIN 0x04001000
#define SP_IMEM_END 0x04001FFF
#define SP_REGISTERS_BEGIN 0x04040000
#define SP_REGISTERS_END 0x0404001F
#define SP_REGISTERS_2_BEGIN 0x04080000
#define SP_REGISTERS_2_END 0x04080007
#define DP_COMMAND_REGISTERS_BEGIN 0x04100000
#define DP_COMMAND_REGISTERS_END 0x0410001F
#define DP_SPAN_REGISTERS_BEGIN 0x04200000
#define DP_SPAN_REGISTERS_END 0x0420000F
#define MI_REGISTERS_BEGIN 0x04300000
#define MI_REGISTERS_END 0x0430000F
#define VI_REGISTERS_BEGIN 0x04400000
#define VI_REGISTERS_END 0x04400037
#define AI_REGISTERS_BEGIN 0x04500000
#define AI_REGISTERS_END 0x04500017
#define PI_REGISTERS_BEGIN 0x04600000
#define PI_REGISTERS_END 0x04600033
#define RI_REGISTERS_BEGIN 0x04700000
#define RI_REGISTERS_END 0x0470001F
#define SI_REGISTERS_BEGIN 0x04800000
#define SI_REGISTERS_END 0x0480001B
#define ROM_BEGIN 0x10000000
#define ROM_END 0x1FBFFFFF

// Memory offsets
#define RDRAM_OFFSET 0x0
#define RDRAM_REGISTERS_OFFSET 0x03F00000
#define SP_DMEM_OFFSET 0x04000000
#define SP_IMEM_OFFSET 0x04001000
#define SP_REGISTERS_OFFSET 0x04040000
#define SP_REGISTERS_2_OFFSET 0x04080000
#define DP_COMMAND_REGISTERS_OFFSET 0x04100000
#define DP_SPAN_REGISTERS_OFFSET 0x04200000
#define MI_REGISTERS_OFFSET 0x04300000
#define VI_REGISTERS_OFFSET 0x04400000
#define AI_REGISTERS_OFFSET 0x04500000
#define PI_REGISTERS_OFFSET 0x04600000
#define RI_REGISTERS_OFFSET 0x04700000
#define SI_REGISTERS_OFFSET 0x04800000
#define ROM_OFFSET 0x10000000

// Defines a memory section within the system
typedef struct MemorySection {
    uint32_t offset;
    void *pointer;
} MemorySection;

// Stores the rom data
typedef struct Rom {
    unsigned char* data;
    size_t sz;
} Rom;

// The memory structure for the system
typedef struct Memory {
    unsigned char rdram[0x400000];
    unsigned char rdram_registers[0x28];
    unsigned char sp_dmem[0x1000];
    unsigned char sp_imem[0x1000];
    unsigned char sp_registers[0x20];
    unsigned char sp_registers2[0x8];
    unsigned char pi_registers[0x34];
    unsigned char vi_registers[0x38];
    unsigned char ai_registers[0x18];
    unsigned char dp_command_registers[0x20];
    unsigned char dp_span_registers[0x10];
    unsigned char mi_registers[0x10];
    unsigned char ri_registers[0x20];
    unsigned char si_registers[0x1c];
    Rom* rom; 
} Memory;

// Creates a new memory
Memory* memory_create();

// Performs cleanup
void memory_destroy(Memory* memory);

// Loads a ROM binary file
void memory_load_rom(Memory* memory, char* path);

// Gets the memory section that a given address belongs to
MemorySection* memory_get_section(Memory* memory, uint32_t addr);

// Reads a byte from memory
uint8_t memory_read_byte(Memory* memory, uint32_t addr);

// Reads a half word from memory
uint16_t memory_read_hword(Memory* memory, uint32_t addr);

// Reads a word from memory
uint32_t memory_read_word(Memory* memory, uint32_t addr);

// Writes a byte to memory
void memory_write_byte(Memory* memory, uint32_t addr, uint8_t value);

// Writes a half word to memory
void memory_write_hword(Memory* memory, uint32_t addr, uint16_t value);

// Writes a word to memory
void memory_write_word(Memory* memory, uint32_t addr, uint32_t value);

#endif

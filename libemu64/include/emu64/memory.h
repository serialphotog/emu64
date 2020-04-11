#pragma once

#include "emu64/memory_section.h"
#include "emu64/rom.h"

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

namespace Emu64 
{
    class Memory
    {
        public:
            Memory();
            ~Memory();

            // Read/Write a single byte from/to memory
            uint8_t ReadByte(uint32_t addr);
            void WriteByte(uint32_t addr, uint8_t value);

            // Read/Write a half word from/to memory
            uint16_t ReadHWord(uint32_t addr);
            void WriteHWord(uint32_t addr, uint16_t value);

            // Read/write a word from/to memory
            uint32_t ReadWord(uint32_t addr);
            void WriteWord(uint32_t addr, uint32_t value);

        private:
            // The memory sections
            unsigned char m_rdram[0x400000];
            unsigned char m_rdram_registers[0x28];
            unsigned char m_sp_dmem[0x1000];
            unsigned char m_sp_imem[0x1000];
            unsigned char m_sp_registers[0x20];
            unsigned char m_sp_registers2[0x8];
            unsigned char m_pi_registers[0x34];
            unsigned char m_vi_registers[0x38];
            unsigned char m_ai_registers[0x18];
            unsigned char m_dp_command_registers[0x20];
            unsigned char m_dp_span_registers[0x10];
            unsigned char m_mi_registers[0x10];
            unsigned char m_ri_registers[0x20];
            unsigned char m_si_registers[0x1c];
            Emu64::Rom* m_rom = nullptr; 

            // Converts a virtual address to a physical address
            uint32_t MapVirtAddr(uint32_t virt_addr);

            // Gets the memory section that an address belongs to
            Emu64::MemorySection* GetSectionForAddr(uint32_t addr);

            // Performs a byte swap on a 32-bit value. 
            inline uint32_t Swap32(uint32_t value) 
            {
                return ((value >> 24) & 0xff) |
                    ((value << 8) & 0xff0000) |
                    ((value >> 8) & 0xff00) |
                    ((value << 24) & 0xff000000);
            }
    };
}
#include "emu64/memory.h"

#include <iostream>

namespace Emu64
{
    Memory::Memory()
    {

    }

    Memory::~Memory()
    {
        if (m_rom != nullptr) delete m_rom;
    }

    Emu64::MemorySection* Memory::GetSectionForAddr(uint32_t addr)
    {
        if ((addr >= RDRAM_BEGIN) && (addr <= RDRAM_END)) // RDRAM
            return new Emu64::MemorySection(RDRAM_OFFSET, m_rdram);

        if ((addr >= RDRAM_REGISTERS_BEGIN) && (addr <= RDRAM_REGISTERS_END)) // RDRAM Registers
            return new Emu64::MemorySection(RDRAM_REGISTERS_OFFSET, m_rdram_registers);

        if ((addr >= SP_DMEM_BEGIN) && (addr <= SP_DMEM_END)) // SP_DMEM
            return new Emu64::MemorySection(SP_DMEM_OFFSET, m_sp_dmem);

        if ((addr >= SP_IMEM_BEGIN) && (addr <= SP_IMEM_END)) // SP_IMEM
            return new Emu64::MemorySection(SP_IMEM_OFFSET, m_sp_imem);

        if ((addr >= SP_REGISTERS_BEGIN) && (addr <= SP_REGISTERS_END)) // SP_REGISTERS
            return new Emu64::MemorySection(SP_REGISTERS_OFFSET, m_sp_registers);

        if ((addr >= SP_REGISTERS_2_BEGIN) && (addr <= SP_REGISTERS_2_END)) // SP_REGISTERS2
            return new Emu64::MemorySection(SP_REGISTERS_2_OFFSET, m_sp_registers2);

        if ((addr >= DP_COMMAND_REGISTERS_BEGIN) && (addr <= DP_COMMAND_REGISTERS_END)) // DP_COMMAND_REGISTERS
            return new Emu64::MemorySection(DP_COMMAND_REGISTERS_OFFSET, m_dp_command_registers);

        if ((addr >= DP_SPAN_REGISTERS_BEGIN) && (addr <= DP_SPAN_REGISTERS_END)) // DP_SPAN_REGISTERS
            return new Emu64::MemorySection(DP_SPAN_REGISTERS_OFFSET, m_dp_span_registers);

        if ((addr >= MI_REGISTERS_BEGIN) && (addr <= MI_REGISTERS_END)) // MI_REGISTERS
            return new Emu64::MemorySection(MI_REGISTERS_OFFSET, m_mi_registers);

        if ((addr >= VI_REGISTERS_BEGIN) && (addr <= VI_REGISTERS_END)) // VI_REGISTERS
            return new Emu64::MemorySection(VI_REGISTERS_OFFSET, m_vi_registers);

        if ((addr >= AI_REGISTERS_BEGIN) && (addr <= AI_REGISTERS_END)) // AI_REGISTERS
            return new Emu64::MemorySection(AI_REGISTERS_OFFSET, m_ai_registers);

        if ((addr >= PI_REGISTERS_BEGIN) && (addr <= PI_REGISTERS_END)) // PI_REGISTERS
            return new Emu64::MemorySection(PI_REGISTERS_OFFSET, m_pi_registers);

        if ((addr >= RI_REGISTERS_BEGIN) && (addr <= RI_REGISTERS_END)) // RI_REGISTERS
            return new Emu64::MemorySection(RI_REGISTERS_OFFSET, m_ri_registers);

        if ((addr >= SI_REGISTERS_BEGIN) && (addr <= SI_REGISTERS_END)) // SI_REGISTERS
            return new Emu64::MemorySection(SI_REGISTERS_OFFSET, m_si_registers);

        if ((addr >= ROM_BEGIN) && (addr <= ROM_END)) // ROM
        {
            if (m_rom == nullptr)
            {
                // TODO: This needs to have actual error handling
                std::cout << "[ERROR]: No ROM loaded!" << std::endl;
                return nullptr;
            }

            if ((addr - ROM_OFFSET) > m_rom->Size())
            {
                // Illegal address
                // TODO: This needs actual error handling!
                std::cout << "[ERROR]: Physical address " << std::hex << addr 
                    << std::dec << " is out of bounds!" << std::endl;
                return nullptr;
            }

            return new Emu64::MemorySection(ROM_OFFSET, m_rom->Data());
        }
    }

    void Memory::LoadRom(const std::string path)
    {
        m_rom = new Emu64::Rom();
        m_rom->Read(path);
    }

    uint32_t Memory::MapVirtAddr(uint32_t virt_addr)
    {
        return virt_addr & 0x1FFFFFFF;
    }

    uint8_t Memory::ReadByte(uint32_t addr)
    {
        uint32_t phys_addr = MapVirtAddr(addr);
        Emu64::MemorySection* section = GetSectionForAddr(phys_addr);
        uint8_t* ptr = (uint8_t*) section->Pointer();
        return ptr[phys_addr - section->Offset()];
    }

    void Memory::WriteByte(uint32_t addr, uint8_t value)
    {
        uint32_t phys_addr = MapVirtAddr(addr);
        Emu64::MemorySection* section = GetSectionForAddr(phys_addr);
        uint8_t* ptr = (uint8_t*) section->Pointer();
        ptr[phys_addr - section->Offset()] = value;
    }

    uint16_t Memory::ReadHWord(uint32_t addr)
    {
        uint32_t phys_addr = MapVirtAddr(addr);
        Emu64::MemorySection* section = GetSectionForAddr(phys_addr);
        uint32_t pointer = phys_addr - section->Offset();
        if (pointer)
            pointer /= 2;
        uint16_t* ptr = (uint16_t*) section->Pointer();
        return ptr[pointer];
    }

    void Memory::WriteHWord(uint32_t addr, uint16_t value)
    {
        uint32_t phys_addr = MapVirtAddr(addr);
        Emu64::MemorySection* section = GetSectionForAddr(phys_addr);
        uint32_t pointer = phys_addr - section->Offset();
        if (pointer)
            pointer /= 2;
        uint16_t* ptr = (uint16_t*) section->Pointer();
        ptr[pointer] = value;
    }

    uint32_t Memory::ReadWord(uint32_t addr)
    {
        uint32_t phys_addr = MapVirtAddr(addr);
        Emu64::MemorySection* section = GetSectionForAddr(phys_addr);
        uint32_t pointer = phys_addr - section->Offset();
        if (pointer)
            pointer /= 4;
        uint32_t* ptr = (uint32_t*) section->Pointer();
        return Swap32(ptr[pointer]);
    }

    void Memory::WriteWord(uint32_t addr, uint32_t value)
    {
        uint32_t phys_addr = MapVirtAddr(addr);
        Emu64::MemorySection* section = GetSectionForAddr(phys_addr);
        uint32_t pointer = phys_addr - section->Offset();
        if (pointer)
            pointer /= 4;
        uint32_t* ptr = (uint32_t*) section->Pointer();
        ptr[pointer] = Swap32(value);
    }
}
#include "emu64/system.h"

#include "emu64/pif.h"

#include <iostream>

namespace Emu64
{
    System::System()
    {
        m_cpu = cpu_create();
        m_memory = memory_create();
    }

    System::~System()
    {
        cpu_destory(m_cpu);
    }

    void System::LoadRom(char* path)
    {
        std::cout << "[INFO]: Loaded rom " << path << std::endl;
        memory_load_rom(m_memory, path);
    }

    void System::Boot()
    {
        std::cout << "[INFO]: Running the emulated PIF." << std::endl;
        Emu64::PIF::Run(m_cpu, m_memory);
        std::cout << "[INFO]: Handing execution over to the CPU." << std::endl;
        cpu_run(m_cpu, m_memory);
    }
}
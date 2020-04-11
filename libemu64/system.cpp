#include "emu64/system.h"

#include "emu64/pif.h"

#include <iostream>

namespace Emu64
{
    System* System::m_instance = nullptr;
    System* System::Instance()
    {
        if (!m_instance)
            m_instance = new System();
        return m_instance;
    }

    System::System()
    {
        m_memory = new Emu64::Memory();
        m_cpu = new Emu64::Processor::CPU(m_memory);
    }

    System::~System()
    {
        delete m_cpu;
        delete m_memory;
    }

    void System::LoadRom(char* path)
    {
        std::cout << "[INFO]: Loaded rom " << path << std::endl;
        m_memory->LoadRom(path);
    }

    void System::Boot()
    {
        std::cout << "[INFO]: Running the emulated PIF." << std::endl;
        Emu64::PIF::Run(m_cpu, m_memory);
        std::cout << "[INFO]: Handing execution over to the CPU." << std::endl;
        m_cpu->Run();
    }
}
#pragma once

// Old C api includes
// TODO: Port over to C++
#include "emu64/sys/cpu/cpu.h"
#include "emu64/sys/memory.h"

namespace Emu64
{
    class System
    {
        public:
            System();
            ~System();

            // Loads a rom into the system
            void LoadRom(char* path);

            // Emulates the boot process of the system
            void Boot();

        private:
            CPU* m_cpu;
            Memory* m_memory;
    };
}
#pragma once

#include "emu64/memory.h"
#include "emu64/vr4300/cpu.h"

namespace Emu64
{
    class System
    {
        public: 
            // Gets the singleton instance
            static System* Instance();

            // Performs cleanup
            ~System();

            // Loads a rom into the system
            void LoadRom(char* path);

            // Emulates the boot process of the system
            void Boot();

        private:
            // the singleton instance
            static System* m_instance;

            // The system's CPU
            Emu64::Processor::CPU* m_cpu;

            // The system's memory subsystem
            Emu64::Memory* m_memory;

            // Needed for singleton
            System();
            System(System const&) = delete;
            System& operator=(System const&) = delete;

    };
}
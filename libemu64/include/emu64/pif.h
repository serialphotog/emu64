#pragma once

extern "C" {
    #include "emu64/sys/cpu/cpu.h"
    #include "emu64/sys/memory.h"
}

namespace Emu64
{
    class PIF
    {
        public:
            static void Run(CPU* cpu, Memory* memory);
    };
}
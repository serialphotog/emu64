#pragma once

#include "emu64/memory.h"
#include "emu64/vr4300/cpu.h"

namespace Emu64
{
    class PIF
    {
        public:
            static void Run(Emu64::Processor::CPU* cpu, Emu64::Memory* memory);
    };
}
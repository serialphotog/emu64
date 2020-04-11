#pragma once

#include "emu64/vr4300/register.h"

#include <map>
#include <string>
#include <vector>

namespace Emu64::Processor
{
    class ProcessorState
    {
        public:
            // Initializes the processor state
            ProcessorState(std::vector<Emu64::Processor::Register*> generalRegs,
                std::map<std::string, Emu64::Processor::Register*> specialRegs);

            // Performs cleanup
            ~ProcessorState();

            // Gets a specific general register
            Emu64::Processor::Register* GetRegister(size_t rnum);

            // Finds a general purpose register based on its name
            Emu64::Processor::Register* GetRegisterByName(std::string name);

            // Gets a special register
            Emu64::Processor::Register* GetSpecialRegister(std::string rname);

        private:
            // Stores general, numbered registers
            std::vector<Emu64::Processor::Register*> m_generalRegisters;

            // Stores named, special registers. A classic example would be the SP
            std::map<std::string, Emu64::Processor::Register*> m_specialRegisters;
    };
}
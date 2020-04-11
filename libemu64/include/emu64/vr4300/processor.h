#pragma once

#include "emu64/memory.h"
#include "emu64/vr4300/processor_state.h"

#include <map>
#include <string>
#include <vector>

namespace Emu64::Processor
{
    class Processor
    {
        public:
            // Initializes a processor
            Processor(Emu64::Memory* memory);
            ~Processor();

            // Sets a general purpose register by index
            void SetRegister(int idx, uint64_t value);

            // Sets a general purpose register by name
            void SetRegisterByName(std::string name, uint64_t value);

            // Sets the value of a special register
            void SetSpecial(std::string name, uint64_t value);

        protected:
            // Stores the processor state
            Emu64::Processor::ProcessorState* m_state;

            // Pointer to the system memory
            Emu64::Memory* m_memory;

            // Initializes the general purpose registers
            virtual std::vector<Emu64::Processor::Register*> InitGPRs() = 0;

            // Initializes the special purpose registers
            virtual std::map<std::string, Emu64::Processor::Register*> InitSpecial() = 0;

    };
}
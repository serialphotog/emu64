#pragma once

#include "emu64/vr4300/processor.h"

namespace Emu64::Processor
{
    class CP0 : public Emu64::Processor::Processor
    {
         public:
            // Initializes the processor state
            CP0(Emu64::Memory* memory);

            // Gets the state
            Emu64::Processor::ProcessorState* State() const { return m_state; }

        protected:
            // Initializes the general purpose registers
            std::vector<Emu64::Processor::Register*> InitGPRs();

            // Initializes the special purpose registers
            std::map<std::string, Emu64::Processor::Register*> InitSpecial();
    };
}
#pragma once

#include "emu64/vr4300/cp0.h"
#include "emu64/vr4300/processor.h"
#include "emu64/vr4300/instruction.h"

namespace Emu64::Processor
{
    class CPU : public Emu64::Processor::Processor
    {
        public:
            // Initializes the processor state
            CPU(Emu64::Memory* memory);

            // Starts the run loop for the processor
            void Run();

            // Gets the CP0 instance
            Emu64::Processor::CP0* CP0() const { return m_cp0; }

        protected:
            // Initializes the general purpose registers
            std::vector<Emu64::Processor::Register*> InitGPRs();

            // Initializes the special purpose registers
            std::map<std::string, Emu64::Processor::Register*> InitSpecial();

        private:
             // Pointer to the CP0 coprocessor
            Emu64::Processor::CP0* m_cp0;

            // Performs an instruction fetch
            Emu64::Processor::Instruction* FetchInstruction();

            // Runs an instruction
            void RunInstruction(Emu64::Processor::Instruction* instruction);

            // Increment the PC
            void IncPC(int amt);

            //
            // CPU Instructions
            //

            /**
             * Moves the contents of the word in cpu reg rt, to cp0 reg rd.
            */
           void MTC0(uint8_t rt, uint8_t rd);

           /**
            * Load upper limit
            * rt = imm << 16
            */
           void LUI(uint8_t rt, uint16_t imm);

            /**
             * Add Imediate Unsigned
             * rt = rs + imm
            */
            void ADDIU(uint8_t rs, uint8_t rt, uint16_t imm);
    };
}
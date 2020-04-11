#pragma once

#include <cstdint>

namespace Emu64::Processor
{
    class Instruction
    {
        public:
            Instruction(); 
            Instruction(uint32_t instruction);

            // Decodes the instruction
            void Decode();

            // Getters
            uint32_t FullInstruction() const { return m_instruction; }
            uint8_t Opcode() const { return m_opcode; }
            uint8_t Base() const { return m_base; }
            uint8_t RS() const { return m_rs; }
            uint8_t RT() const { return m_rt; }
            uint8_t RD() const { return m_rd; }
            uint8_t SA() const { return m_sa; }
            uint8_t Function() const { return m_function; }
            uint16_t Offset() const { return m_offset; }

            // Setters
            void FullInstruction(const uint32_t instruction) { m_instruction = instruction; }
            void Opcode(const uint8_t opcode) { m_opcode = opcode; }
            void Base(const uint8_t base) { m_base = base; }
            void RS(const uint8_t rs) { m_rs = rs; }
            void RT(const uint8_t rt) { m_rt = rt; }
            void RD(const uint8_t rd) { m_rd = rd; }
            void SA(const uint8_t sa) { m_sa = sa; }
            void Function(const uint8_t function) { m_function = function; }
            void Offset(const uint16_t offset) { m_offset = offset; }

        private:
            // The full instruction 
            uint32_t m_instruction;
            uint8_t m_opcode;
            uint8_t m_base;
            uint8_t m_rs;
            uint8_t m_rt;
            uint8_t m_rd;
            uint8_t m_sa;
            uint8_t m_function;
            uint16_t m_offset;
    };
}
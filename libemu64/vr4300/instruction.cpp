#include "emu64/vr4300/instruction.h"

namespace Emu64::Processor
{
    Instruction::Instruction()
    {

    }

    Instruction::Instruction(uint32_t instruction) : m_instruction(instruction)
    {

    }

    void Instruction::Decode()
    {
        m_opcode = m_instruction >> 26;
        m_rs = (m_instruction >> 21) & 0x1f;
        m_base = m_rs;
        m_rt = (m_instruction >> 16) & 0x1f;
        m_rd = (m_instruction >> 11) & 0x1f;
        m_sa = (m_instruction >> 6) & 0x1f;
        m_function = m_instruction & 0x3f;
        m_offset = m_instruction & 0xffff;
    }
}
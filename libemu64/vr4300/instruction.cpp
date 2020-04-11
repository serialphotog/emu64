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
        Opcode(FullInstruction() >> 26);
        RS((FullInstruction() >> 21) & 0x1f);
        Base(RS());
        RT((FullInstruction() >> 16) & 0x1f);
        RD((FullInstruction() >> 11) & 0x1f);
        SA((FullInstruction() >> 6) & 0x1f);
        Function(FullInstruction() & 0x3f);
        Offset(FullInstruction() & 0xffff);
    }
}
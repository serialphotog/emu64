#include "emu64/vr4300/processor.h"

namespace Emu64::Processor
{
    Processor::Processor(Emu64::Memory* memory) : m_memory(memory)
    {

    }

    Processor::~Processor()
    {
        delete m_state;
    }

    void Processor::SetRegister(int idx, uint64_t value)
    {
        Emu64::Processor::Register* reg = m_state->GetRegister(idx);
        reg->Data(value);
    }

    void Processor::SetRegisterByName(std::string name, uint64_t value)
    {
        Emu64::Processor::Register* reg = m_state->GetRegisterByName(name);
        reg->Data(value);
    }

    void Processor::SetSpecial(std::string name, uint64_t value)
    {
        Emu64::Processor::Register* reg = m_state->GetSpecialRegister(name);
        reg->Data(value);
    }
}
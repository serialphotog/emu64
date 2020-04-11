#include "emu64/vr4300/processor_state.h"

namespace Emu64::Processor
{
    ProcessorState::ProcessorState(std::vector<Emu64::Processor::Register*> generalRegs,
            std::map<std::string, Emu64::Processor::Register*> specialRegs) :
            m_generalRegisters(generalRegs), m_specialRegisters(specialRegs)
    {

    }

    ProcessorState::~ProcessorState()
    {
        // Cleanup the general purpose registers
        for (auto r : m_generalRegisters)
            delete r;
        m_generalRegisters.clear();

        // Clear the special registers
        for (std::pair<std::string, Emu64::Processor::Register*> iter : m_specialRegisters)
            delete iter.second;
        m_specialRegisters.clear();
    }

    Emu64::Processor::Register* ProcessorState::GetRegisterByName(std::string name)
    {
        for (Emu64::Processor::Register* reg : m_generalRegisters)
        {
            if (reg->Name() == name)
                return reg;
        }

        return nullptr;
    }

    Emu64::Processor::Register* ProcessorState::GetRegister(size_t rnum)
    {
        // TODO: There should probably be some actual error checking here!
        if (rnum > m_generalRegisters.size())
            return nullptr;

        return m_generalRegisters[rnum];
    }

    Emu64::Processor::Register* ProcessorState::GetSpecialRegister(std::string rname)
    {
        // TODO: There needs to be error checking here at some point!
        return m_specialRegisters[rname];
    }
}
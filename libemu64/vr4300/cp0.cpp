#include "emu64/vr4300/cp0.h"

namespace Emu64::Processor
{
    CP0::CP0(Emu64::Memory* memory) : Processor(memory)
    {
        // Initialize the state
        std::vector<Emu64::Processor::Register*> generalRegs = InitGPRs();
        std::map<std::string, Emu64::Processor::Register*> specialRegs = InitSpecial();
        m_state = new Emu64::Processor::ProcessorState(generalRegs, specialRegs);
    }

    std::vector<Emu64::Processor::Register*> CP0::InitGPRs()
    {
        std::vector<Emu64::Processor::Register*> generalRegs;
        generalRegs.push_back(new Emu64::Processor::Register("Index", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("Random", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("EntryLo0", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("EntryLo1", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("Context", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("PageMask", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("Wired", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("r7", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("BadVAddr", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("Count", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("EntryHi", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("Compare", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("Status", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("Cause", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("EPC", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("PRId", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("Config", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("LLAddr", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("WatchLo", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("WatchHi", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("XContext", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("r21", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("r22", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("r23", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("r24", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("r25", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("PErr", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("CacheErr", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("TagLo", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("TagHi", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("ErrorEPC", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("r31", NULL));
        return generalRegs;
    }

    std::map<std::string, Emu64::Processor::Register*> CP0::InitSpecial()
    {
        std::map<std::string, Emu64::Processor::Register*> specialRegs;
        // TODO: There are currently no special registers mapped for CP0
        return specialRegs;
    }
}
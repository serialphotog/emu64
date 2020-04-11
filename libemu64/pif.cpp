#include "emu64/pif.h"

#include "emu64/vr4300/cp0.h"

#include <iostream>

namespace Emu64
{
    void PIF::Run(Emu64::Processor::CPU* cpu, Emu64::Memory* memory)
    {
        // Set the general purpose register values
        std::cout << "[PIF]: Initializing the CPU registers" << std::endl;
        cpu->SetRegisterByName("r0", 0);
        cpu->SetRegisterByName("at", 0);
        cpu->SetRegisterByName("v0", 0);
        cpu->SetRegisterByName("v1", 0);
        cpu->SetRegisterByName("a0", 0);
        cpu->SetRegisterByName("a1", 0);
        cpu->SetRegisterByName("a2", 0);
        cpu->SetRegisterByName("a3", 0);
        cpu->SetRegisterByName("t0", 0);
        cpu->SetRegisterByName("t1", 0);
        cpu->SetRegisterByName("t2", 0);
        cpu->SetRegisterByName("t3", 0);
        cpu->SetRegisterByName("t4", 0);
        cpu->SetRegisterByName("t5", 0);
        cpu->SetRegisterByName("t6", 0);
        cpu->SetRegisterByName("t7", 0);
        cpu->SetRegisterByName("s0", 0);
        cpu->SetRegisterByName("s1", 0);
        cpu->SetRegisterByName("s2", 0);
        cpu->SetRegisterByName("s3", 0);
        cpu->SetRegisterByName("s4", 0x1);
        cpu->SetRegisterByName("s5", 0);
        cpu->SetRegisterByName("s6", 0x3f);
        cpu->SetRegisterByName("s7", 0);
        cpu->SetRegisterByName("t8", 0);
        cpu->SetRegisterByName("t9", 0);
        cpu->SetRegisterByName("k0", 0);
        cpu->SetRegisterByName("k1", 0);
        cpu->SetRegisterByName("gp", 0);
        cpu->SetSpecial("sp", 0xa4001ff0);
        cpu->SetRegisterByName("a8", 0);
        cpu->SetRegisterByName("ra", 0);

        // Set the CP0 register values
        std::cout << "[PIF]: Initializing the CP0 registers" << std::endl;
        Emu64::Processor::CP0* cp0 = cpu->CP0();
        cp0->SetRegisterByName("Index", 0);
        cp0->SetRegisterByName("Random", 0x0000001f);
        cp0->SetRegisterByName("EntryLo0", 0);
        cp0->SetRegisterByName("EntryLo1", 0);
        cp0->SetRegisterByName("Context", 0);
        cp0->SetRegisterByName("PageMask", 0);
        cp0->SetRegisterByName("Wired", 0);
        cp0->SetRegisterByName("r7", 0);
        cp0->SetRegisterByName("BadVAddr", 0);
        cp0->SetRegisterByName("Count", 0);
        cp0->SetRegisterByName("EntryHi", 0);
        cp0->SetRegisterByName("Compare", 0);
        cp0->SetRegisterByName("Status", 0x70400004);
        cp0->SetRegisterByName("Cause", 0);
        cp0->SetRegisterByName("EPC", 0);
        cp0->SetRegisterByName("PRId", 0x00000b00);
        cp0->SetRegisterByName("Config", 0x0006e463);
        cp0->SetRegisterByName("LLAddr", 0);
        cp0->SetRegisterByName("WatchLo", 0);
        cp0->SetRegisterByName("WatchHi", 0);
        cp0->SetRegisterByName("XContext", 0);
        cp0->SetRegisterByName("r21", 0);
        cp0->SetRegisterByName("r22", 0);
        cp0->SetRegisterByName("r23", 0);
        cp0->SetRegisterByName("r24", 0);
        cp0->SetRegisterByName("r25", 0);
        cp0->SetRegisterByName("PErr", 0);
        cp0->SetRegisterByName("CacheErr", 0);
        cp0->SetRegisterByName("TagLo", 0);
        cp0->SetRegisterByName("TagHi", 0);
        cp0->SetRegisterByName("ErrorEPC", 0);
        cp0->SetRegisterByName("r31", 0);

        // PIF writes 0x01010101 to 0x04300004
        memory->WriteWord(0x04300004, 0x01010101);

        // Copy the first 0x1000 bytes from cartridge
        std::cout << "[PIF]: Copying initial cart data" << std::endl;
        for (int i=0, offs=0; i < 0x1000; i++, offs++)
        {
            memory->WriteByte(0xA4000000+offs, memory->ReadByte(0xb0000000+offs));
        }

        // Set the PC to begin execution of the cartridge code
        cpu->SetSpecial("pc", 0xffffffffa4000040);
    }
}
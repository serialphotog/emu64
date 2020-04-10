#include "emu64/pif.h"

extern "C" {
    #include "emu64/sys/cpu/cpustate.h"
    #include "emu64/sys/cpu/cp0/cp0.h"
}

#include <iostream>

namespace Emu64
{
    void PIF::Run(CPU* cpu, Memory* memory)
    {
        CPUState* state = cpu->state;
        CP0* cp0 = cpu->cp0;
        CP0State* cp0State = cp0->state;

        // Set the general purpose register values
        std::cout << "[PIF]: Initializing the CPU registers" << std::endl;
        state->r0 = 0;
        state->at = 0;
        state->v0 = 0;
        state->v1 = 0;
        state->a0 = 0;
        state->a1 = 0;
        state->a2 = 0;
        state->a3 = 0;
        state->t0 = 0;
        state->t1 = 0;
        state->t2 = 0;
        state->t3 = 0;
        state->t4 = 0;
        state->t5 = 0;
        state->t6 = 0;
        state->t7 = 0;
        state->s0 = 0;
        state->s1 = 0;
        state->s2 = 0;
        state->s3 = 0;
        state->s4 = 0x1;
        state->s5 = 0;
        state->s6 = 0x3f;
        state->s7 = 0;
        state->t8 = 0;
        state->t9 = 0;
        state->k0 = 0;
        state->k1 = 0;
        state->gp = 0;
        state->sp = 0xa4001ff0;
        state->s8 = 0;
        state->ra = 0;

        // Set the CP0 register values
        std::cout << "[PIF]: Initializing the CP0 registers" << std::endl;
        cp0State->Index = 0;
        cp0State->Random = 0x0000001f;
        cp0State->EntryLo0 = 0;
        cp0State->EntryLo1 = 0;
        cp0State->Context = 0;
        cp0State->PageMask = 0;
        cp0State->Wired = 0;
        cp0State->r7 = 0;
        cp0State->BadVAddr = 0;
        cp0State->Count = 0;
        cp0State->EntryHi = 0;
        cp0State->Compare = 0;
        cp0State->Status = 0x70400004;
        cp0State->Cause = 0;
        cp0State->EPC = 0;
        cp0State->PRId = 0x00000b00;
        cp0State->Config = 0x0006e463;
        cp0State->LLAddr = 0;
        cp0State->WatchLo = 0;
        cp0State->WatchHi = 0;
        cp0State->XContext = 0;
        cp0State->r21 = 0;
        cp0State->r22 = 0;
        cp0State->r23 = 0;
        cp0State->r24 = 0;
        cp0State->r25 = 0;
        cp0State->PErr = 0;
        cp0State->CacheErr = 0;
        cp0State->TagLo = 0;
        cp0State->TagHi = 0;
        cp0State->ErrorEPC = 0;
        cp0State->r31 = 0;

        // PIF writes 0x01010101 to 0x04300004
        memory_write_word(memory, 0x04300004, 0x01010101);

        // Copy the first 0x1000 bytes from cartridge
        std::cout << "[PIF]: Copying initial cart data" << std::endl;
        for (int i=0, offs=0; i < 0x1000; i++, offs++)
        {
            memory_write_byte(memory, 0xA4000000+offs, memory_read_byte(memory, 0xb0000000+offs));
        }

        // Set the PC to begin execution of the cartridge code
        state->pc = 0xffffffffa4000040;
    }
}
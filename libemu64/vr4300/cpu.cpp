#include "emu64/vr4300/cpu.h"

#include "emu64/vr4300/opcodes.h"

#include <iostream>

namespace Emu64::Processor
{
    CPU::CPU(Emu64::Memory* memory) : Processor(memory)
    {
        // Initialize the state
        std::vector<Emu64::Processor::Register*> generalRegs = InitGPRs();
        std::map<std::string, Emu64::Processor::Register*> specialRegs = InitSpecial();
        m_state = new Emu64::Processor::ProcessorState(generalRegs, specialRegs);

        // Initialize the coprocessor
        m_cp0 = new Emu64::Processor::CP0(m_memory);
    }

    std::vector<Emu64::Processor::Register*> CPU::InitGPRs()
    {
        /* The VR4300 contains 32, 64-bit GPRs. Two of these registers are assigned
        * speical functions:
        * 
        * R0: hardwired to 0. Can be used as the target register for any
        * instruction whose result will be discarded. Can also be used
        * as a source when a zero value is needed.
        * 
        * R31: Link register used by JAL JALR instructions. Can be used
        * by other instructions. Must ensure that data from other instructions
        * does not overlap JAL/JALR instructions.
        */
        std::vector<Emu64::Processor::Register*> generalRegs;
        generalRegs.push_back(new Emu64::Processor::Register("r0", 0x0)); // This one remains 0 always
        generalRegs.push_back(new Emu64::Processor::Register("at", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("v0", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("v1", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("a0", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("a1", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("a2", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("a3", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t0", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t1", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t2", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t3", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t4", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t5", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t6", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t7", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s0", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s1", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s2", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s3", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s4", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s5", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s6", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s7", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t8", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("t9", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("k0", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("k1", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("gp", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("sp", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("s8", NULL));
        generalRegs.push_back(new Emu64::Processor::Register("ra", NULL));
        return generalRegs;
    }

    std::map<std::string, Emu64::Processor::Register*> CPU::InitSpecial()
    {
        std::map<std::string, Emu64::Processor::Register*> specialRegs;
        specialRegs["pc"] = new Emu64::Processor::Register("pc", NULL);
        specialRegs["hi"] = new Emu64::Processor::Register("hi", NULL);
        specialRegs["lo"] = new Emu64::Processor::Register("lo", NULL);
        // TODO: The CPU has special registers that aren't 64-bit. This will
        // require some templating magis in the register class later to fix.
        return specialRegs;
    }

    Emu64::Processor::Instruction* CPU::FetchInstruction()
    {
        Emu64::Processor::Register* sp = m_state->GetSpecialRegister("sp");
        uint32_t data = m_memory->ReadWord(sp->Data());
        Emu64::Processor::Instruction* instruction = new Emu64::Processor::Instruction(data);
        instruction->Decode();
        return instruction;
    }

    void CPU::RunInstruction(Emu64::Processor::Instruction* instruction)
    {
        switch(instruction->Opcode())
        {
            case OP_MFC0:
                if (instruction->RS() == MFC0_RS_FLAG)
                {
                    std::cout << "Found MFC0. Implement me!" << std::endl;
                }
                else if (instruction->RS() == MTC0_RS_FLAG)
                {
                    MTC0(instruction->RT(), instruction->RD());
                }
                else 
                {
                    std::cout << "[CPU]: Unknown MFC0/MTC0 flag: " << std::hex << instruction->RS() 
                        << std::dec << std::endl;
                }
                break;
            case OP_LUI:
                LUI(instruction->RT(), instruction->Offset());
                break;
            case OP_ADDIU:
                ADDIU(instruction->RS(), instruction->RT(), instruction->Offset());
                break;
            default:
                std::cout << "[CPU]: Unknown instruction: " << std::hex << instruction->Opcode()
                    << std::dec << std::endl;
                break;
        }
    }

    void CPU::Run()
    {
        while(1)
        {
            // TODO: We need a more robust run loop system
            Emu64::Processor::Instruction* instruction = FetchInstruction();
            RunInstruction(instruction);
        }
    }

    void CPU::IncPC(int amt)
    {
        Emu64::Processor::Register* pc = m_state->GetSpecialRegister("pc");
        pc->Data(pc->Data() + amt);
    }

    void CPU::MTC0(uint8_t rt, uint8_t rd)
    {
        Emu64::Processor::Register* src = m_state->GetRegister(rt);
        Emu64::Processor::Register* dest = m_cp0->State()->GetRegister(rd);
        dest->Data(src->Data());
        IncPC(4);
    }

    void CPU::LUI(uint8_t rt, uint16_t imm)
    {
        Emu64::Processor::Register* dest = m_state->GetRegister(rt);
        dest->Data((uint64_t)(imm << 16));
        IncPC(4);
    }

    void CPU::ADDIU(uint8_t rs, uint8_t rt, uint16_t imm)
    {
        Emu64::Processor::Register* dest = m_state->GetRegister(rt);
        Emu64::Processor::Register* src = m_state->GetRegister(rs);
        dest->Data(src->Data() + (uint16_t)imm);
        IncPC(4);
    }
}
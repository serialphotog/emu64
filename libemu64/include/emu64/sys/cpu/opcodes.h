#ifndef __EMU_OPCODES_H__
#define __EMU_OPCODES_H__

// Opcode definitions
#define OP_MFC0 0x10
#define OP_MTC0 OP_MFC0
#define OP_LUI 0x0f
#define OP_ADDIU 0x09

// Switch definitions for opcodes
#define MFC0_RS_FLAG 0x0
#define MTC0_RS_FLAG 0x4

#endif
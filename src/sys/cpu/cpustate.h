#ifndef __EMU_CPU_STATE_H__
#define __EMU_CPU_STATE_H__

#include <stdint.h>

// The CPU state store structure
typedef struct CPUState {
    /* General Purpose Registers
     * 
     * The VR4300 contains 32, 64-bit GPRs. Two of these registers are assigned
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
    uint64_t r0; // See note above about special function
    uint64_t at; // r1
    uint64_t v0; // r2
    uint64_t v1; // r3
    uint64_t a0; // r4
    uint64_t a1; // r5
    uint64_t a2; // r6
    uint64_t a3; // r7
    uint64_t t0; // r8
    uint64_t t1; // r9
    uint64_t t2; // r10
    uint64_t t3; // r11
    uint64_t t4; // r12
    uint64_t t5; // r13
    uint64_t t6; // r14
    uint64_t t7; // r15
    uint64_t s0; // r16
    uint64_t s1; // r17
    uint64_t s2; // r18
    uint64_t s3; // r19
    uint64_t s4; // r20
    uint64_t s5; // r21
    uint64_t s6; // r22
    uint64_t s7; // r23
    uint64_t t8; // r24
    uint64_t t9; // r25
    uint64_t k0; // r26
    uint64_t k1; // r27
    uint64_t gp; // r28
    uint64_t sp; // r29
    uint64_t s8; // r30
    uint64_t ra; // r31. See note above about special funciton

    /* Floating Point Operation Registers
     * 
     * The VR4300 contains 32, 64-bit FPRs
     */
    uint64_t fpr0;
    uint64_t fpr1;
    uint64_t fpr2;
    uint64_t fpr3;
    uint64_t fpr4;
    uint64_t fpr5;
    uint64_t fpr6;
    uint64_t fpr7;
    uint64_t fpr8;
    uint64_t fpr9;
    uint64_t fpr10;
    uint64_t fpr11;
    uint64_t fpr12;
    uint64_t fpr13;
    uint64_t fpr14;
    uint64_t fpr15;
    uint64_t fpr16;
    uint64_t fpr17;
    uint64_t fpr18;
    uint64_t fpr19;
    uint64_t fpr20;
    uint64_t fpr21;
    uint64_t fpr22;
    uint64_t fpr23;
    uint64_t fpr24;
    uint64_t fpr25;
    uint64_t fpr26;
    uint64_t fpr27;
    uint64_t fpr28;
    uint64_t fpr29;
    uint64_t fpr30;
    uint64_t fpr31;

    // Special Purpose Registers
    uint64_t pc; // The program counter register
    uint8_t llibt; // Load/Link llbit register. Note that this is only 1-bit on silicone

    /**
     * The HI and LO registers contain the integer multiply and divide
     * high and low order doubleword result, respectively.
     */
    uint64_t hi;
    uint64_t lo;

    uint32_t fcr0; // floating point implementation/revision register
    uint32_t fcr31; // float point control/status register
} CPUState;

// Maps a register number to a physical register
uint64_t* cpu_map_register(CPUState* state, uint8_t reg);

// Creates a new CPU state instance
CPUState* cpuState_create();

// Cleanup
void cpuState_destroy(CPUState* state);

#endif
/**
 * CP0 is the coprocessor that supports control tasks, such as virtual memory and exception processing.
 */

#ifndef __EMU_CP0_H__
#define __EMU_CP0_H__

#include <stdint.h>

// MIPS memory region definitions
// Refer to table 5-3 in the CR3400 manual
#define KSEG0_VIRT_BEGIN 0xffffffff80000000
#define KSEG1_VIRT_BEGIN 0xffffffffa0000000

// The internal state for the coprocessor
typedef struct CP0State {
    /**
     * CP0 registers.
     */
    uint64_t Index;
    uint64_t Random;
    uint64_t EntryLo0;
    uint64_t EntryLo1;
    uint64_t Context;
    uint64_t PageMask;
    uint64_t Wired;
    uint64_t r7; // RESERVED
    uint64_t BadVAddr;
    uint64_t Count;
    uint64_t EntryHi;
    uint64_t Compare;
    uint64_t Status;
    uint64_t Cause;
    uint64_t EPC;
    uint64_t PRId;
    uint64_t Config;
    uint64_t LLAddr;
    uint64_t WatchLo;
    uint64_t WatchHi;
    uint64_t XContext;
    uint64_t r21; // RESERVED
    uint64_t r22; // RESERVED
    uint64_t r23; // RESERVED
    uint64_t r24; // RESERVED
    uint64_t r25; // RESERVED
    uint64_t PErr; // Parity error
    uint64_t CacheErr;
    uint64_t TagLo;
    uint64_t TagHi;
    uint64_t ErrorEPC;
    uint64_t r31; // RESERVED
} CP0State;

// The System Control Coprocessor (CP0) structure
typedef struct CP0 {
    CP0State* state; // The internal state for CP0
} CP0;

// Maps a register number to a physical register
uint64_t* cp0_map_register(CP0* cp0, uint8_t reg);

// Creates a new CP0 instance
CP0* cp0_create();

// Perform cleanup
void cp0_destroy(CP0* cp0);

#endif

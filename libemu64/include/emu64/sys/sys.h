#ifndef __EMU_SYS_H__
#define __EMU_SYS_H__

#include "emu64/sys/cpu/cpu.h"
#include "emu64/emu64.h"
#include "emu64/sys/memory.h"

// The primary system structure
typedef struct System {
    CPU* cpu; // The system's CPU
    Memory* memory; // The system's memory
    EmuFlags* flags; // Emulator control flags
} System;

// Creates the system
System* sys_create(EmuFlags* flags);

// Loads a rom
void sys_load_rom(System* sys, const char* path);

// Emulates the boot process of the system
void sys_boot(System* sys);

// Performs cleanup
void sys_destroy(System* sys);

#endif

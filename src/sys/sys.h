#ifndef __EMU_SYS_H__
#define __EMU_SYS_H__

#include "sys/cpu/cpu.h"
#include "sys/memory.h"

// The primary system structure
typedef struct System {
    CPU* cpu; // The system's CPU
    Memory* memory; // The system's memory
} System;

// Creates the system
System* sys_create();

// Loads a rom
void sys_load_rom(System* sys, const char* path);

// Emulates the boot process of the system
void sys_boot(System* sys);

// Performs cleanup
void sys_destroy(System* sys);

#endif

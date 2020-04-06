#include "sys/sys.h"

#include <stdlib.h>
#include <stdio.h>

#include "sys/pif.h"

System* sys_create(EmuFlags* flags) 
{
    System* sys = calloc(1, sizeof(System));
    sys->cpu = cpu_create(flags);
    sys->memory = memory_create();
    sys->flags = flags;
    
    return sys;
}

void sys_load_rom(System* sys, const char* path)
{
    printf("[INFO]: Loaded rom %s\n", path);
    memory_load_rom(sys->memory, path);
}

void sys_boot(System* sys) 
{
    // Run an emulation of the PIF ROM
    printf("[INFO]: Running the emulated PIF.\n");
    pif_run(sys);
    printf("[INFO]: Handing execution over to the CPU.\n");
    cpu_run(sys->cpu, sys->memory);
}

void sys_destroy(System* sys) 
{
    cpu_destory(sys->cpu);
    free(sys);
}

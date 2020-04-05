#include "sys/sys.h"

#include <stdlib.h>
#include <stdio.h>

#include "sys/pif.h"

System* sys_create(char* rom_path) 
{
    System* sys = calloc(1, sizeof(System));
    sys->cpu = cpu_create();
    sys->memory = memory_create();
    memory_load_rom(sys->memory, rom_path);
    
    return sys;
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

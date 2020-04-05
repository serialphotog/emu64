#include "sys/cpu/cp0/cp0.h"

#include <stdlib.h>
#include <stdio.h>

CP0* cp0_create() 
{
    CP0* cp0 = calloc(1, sizeof(CP0));
    cp0->state = calloc(1, sizeof(CP0State));

    return cp0;
}

uint32_t virt_addr_to_phys_addr(uint64_t virt_addr)
{
    // Refer to table 5-3 in the VR3400 manual.
    uint32_t phys_addr;
    uint64_t addr_bit_values = (virt_addr >> 29) & 0x7;
    if (addr_bit_values == 0x5) // 0b101
    {
        // KSEG1
        phys_addr = virt_addr - KSEG1_VIRT_BEGIN; 
    }
    else if (addr_bit_values == 0x4) // 0b100
    {
        // KSEG0
        phys_addr = virt_addr - KSEG0_VIRT_BEGIN;
    }
    else
    {
        printf("[ERROR]: Unrecognized virtual address encountered: %#010lx\n", virt_addr);
    }

    return phys_addr;
}

void cp0_destroy(CP0* cp0) 
{
    free(cp0->state);
    free(cp0);
}

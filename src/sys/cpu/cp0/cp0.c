#include "sys/cpu/cp0/cp0.h"

#include <stdlib.h>
#include <stdio.h>

CP0* cp0_create() 
{
    CP0* cp0 = calloc(1, sizeof(CP0));
    cp0->state = calloc(1, sizeof(CP0State));

    return cp0;
}

uint64_t* cp0_map_register(CP0* cp0, uint8_t reg)
{
    CP0State* state = cp0->state;
    switch (reg)
    {
        case 0:
            return &state->Index;
        case 1:
            return &state->Random;
        case 2:
            return &state->EntryLo0;
        case 3:
            return &state->EntryLo1;
        case 4:
            return &state->Context;
        case 5:
            return &state->PageMask;
        case 6:
            return &state->Wired;
        case 7:
            return &state->r7;
        case 8:
            return &state->BadVAddr;
        case 9:
            return &state->Count;
        case 10:
            return &state->EntryHi;
        case 11:
            return &state->Compare;
        case 12:
            return &state->Status;
        case 13:
            return &state->Cause;
        case 14:
            return &state->EPC;
        case 15:
            return &state->PRId;
        case 16:
            return &state->Config;
        case 17:
            return &state->LLAddr;
        case 18:
            return &state->WatchLo;
        case 19:
            return &state->WatchHi;
        case 20:
            return &state->XContext;
        case 21:
            return &state->r21;
        case 22:
            return &state->r22;
        case 23:
            return &state->r23;
        case 24:
            return &state->r24;
        case 25:
            return &state->r25;
        case 26:
            return &state->PErr;
        case 27:
            return &state->CacheErr;
        case 28:
            return &state->TagLo;
        case 29:
            return &state->TagHi;
        case 30:
            return &state->ErrorEPC;
        case 31:
            return &state->r31;
        default:
            printf("[ERROR]: Encountered invalid CP0 register #: %#02x\n", reg);
            exit(1);
            break;
    }
}

void cp0_destroy(CP0* cp0) 
{
    free(cp0->state);
    free(cp0);
}

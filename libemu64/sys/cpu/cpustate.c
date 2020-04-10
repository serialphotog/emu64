#include "emu64/sys/cpu/cpustate.h"

#include <stdlib.h>
#include <stdio.h>

CPUState* cpuState_create()
{
    CPUState* state = calloc(1, sizeof(CPUState));
    return state;
}

uint64_t* cpu_map_register(CPUState* state, uint8_t reg)
{
    switch (reg)
    {
        case 0:
            return &state->r0;
        case 1:
            return &state->at;
        case 2:
            return &state->v0;
        case 3:
            return &state->v1;
        case 4:
            return &state->a0;
        case 5:
            return &state->a1;
        case 6:
            return &state->a2;
        case 7:
            return &state->a3;
        case 8:
            return &state->t0;
        case 9:
            return &state->t1;
        case 10:
            return &state->t2;
        case 11:
            return &state->t3;
        case 12:
            return &state->t4;
        case 13:
            return &state->t5;
        case 14:
            return &state->t6;
        case 15:
            return &state->t7;
        case 16:
            return &state->s0;
        case 17:
            return &state->s1;
        case 18:
            return &state->s2;
        case 19:
            return &state->s3;
        case 20:
            return &state->s4;
        case 21:
            return &state->s5;
        case 22:
            return &state->s6;
        case 23:
            return &state->s7;
        case 24:
            return &state->t8;
        case 25:
            return &state->t9;
        case 26:
            return &state->k0;
        case 27:
            return &state->k1;
        case 28:
            return &state->gp;
        case 29:
            return &state->sp;
        case 30:
            return &state->s8;
        case 31:
            return &state->ra;
        default:
            printf("[ERROR]: Encountered invalid general purpose register #: %#02x\n", reg);
            exit(1);
            break;
    }
}

void cpuState_destroy(CPUState* state) 
{
    free(state);
}
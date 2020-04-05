#include "sys/cpu/cpustate.h"

#include <stdlib.h>

CPUState* cpuState_create()
{
    CPUState* state = calloc(1, sizeof(CPUState));
    return state;
}

void cpuState_destroy(CPUState* state) 
{
    free(state);
}
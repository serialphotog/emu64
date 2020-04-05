#include "sys/cpu/cp0/cp0.h"

#include <stdlib.h>
#include <stdio.h>

CP0* cp0_create() 
{
    CP0* cp0 = calloc(1, sizeof(CP0));
    cp0->state = calloc(1, sizeof(CP0State));

    return cp0;
}

void cp0_destroy(CP0* cp0) 
{
    free(cp0->state);
    free(cp0);
}

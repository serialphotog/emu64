#include "sys/cpu/cp1/cp1.h"

#include <stdlib.h>

CP1* cp1_create()
{
    CP1* cp1 = calloc(1, sizeof(CP1));
    cp1->state = calloc(1, sizeof(CP1State));

    return cp1;
}

void cp1_destroy(CP1* cp1) 
{
    free(cp1->state);
    free(cp1);
}
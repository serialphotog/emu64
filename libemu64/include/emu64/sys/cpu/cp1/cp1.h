/**
 * CP1 acts as the floating-point unit (FPU) of the processor.
 */

#ifndef __EMU_CP1_H__
#define __EMU_CP1_H__

#include <stdint.h>

// The internal state for the fpu
typedef struct CP1State {
    // TODO: Implement the internal state as necessary...
    int foo; // Temporary to silence compiler error for now
} CP1State;

// The main structure for the FPU
typedef struct CP1 {
    CP1State* state; // The internal state for the FPU
} CP1;

// Creates a new CP1 instance
CP1* cp1_create();

// Performs cleanup
void cp1_destroy(CP1* cp1);

#endif
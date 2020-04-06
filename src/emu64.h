#ifndef __EMU_64_H__
#define __EMU_64_H__

#include <stdlib.h>

// Global flags for controlling the emulator
typedef struct EmuFlags {
    int debugMode; // Tracks if debug mode is active
    int singleStepMode; // Tracks if single step mode is active
} EmuFlags;

#endif
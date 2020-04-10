/**
 * Provides the emulation of the PIF ROM from the N64 system.
 * The functionality is implemented according to this document: http://www.emulation64.com/ultra64/bootn64.html
 */

#ifndef __EMU_PIF_H__
#define __EMU_PIF_H__

#include "emu64/sys/sys.h"

// Runs the emulated PIF
void pif_run(System *sys);

#endif
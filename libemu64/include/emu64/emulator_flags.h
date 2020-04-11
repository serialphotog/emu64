#pragma once

namespace Emu64 {
    /**
     * Used for storing current emulator state and allowing communication to the emulator
     * when it is being ran in a different thread.
     */
    typedef struct EmulatorFlags {
        bool EmulatorShouldStop = false;
    } EmulatorFlags;
}
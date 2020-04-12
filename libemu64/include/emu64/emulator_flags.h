#pragma once

#include <atomic>

namespace Emu64 {
    /**
     * Used for storing current emulator state and allowing communication to the emulator
     * when it is being ran in a different thread.
     */
    typedef struct EmulatorFlags {
        std::atomic<bool> Running;
        bool EmulatorShouldStop = false;
    } EmulatorFlags;
}
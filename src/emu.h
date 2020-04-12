#pragma once

#include <thread>

// Provides shared control resources to the emulator frontend
typedef struct ControlFlags {
    std::thread EmulatorThread;
    bool CloseRequested = false;
} ControlFlags;

class Emu
{
    public:
        // Gets the singleton instance of the class
        static Emu* Instance();

        // Gets the control flags
        ControlFlags* ControlFlags() const { return m_controlFlags; }

        // Performs cleanup
        ~Emu();

    private:
        // The instance
        static Emu* m_instance;

        // The control flags instance
        ::ControlFlags* m_controlFlags;

        Emu();
        Emu(Emu const&) = delete;
        Emu& operator=(Emu const&) = delete;
};
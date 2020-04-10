#pragma once

namespace Emu64::UI 
{
    class EmulatorWindow
    {
        public:
            static void ShowEmulatorWindow(bool* is_open);
        
        private:
            static void ShowFileMenu();
    };
}
#include "ui/emulator_window.h"

#include "emu.h"
#include "imgui/imgui.h"
#include "ui/file_browser.h"

#include "emu64/system.h"

#include <string>
#include <thread>

namespace Emu64::UI
{
    static void runEmulatorThread()
    {
        Emu64::System* system = Emu64::System::Instance();
        system->Boot();
    }

    void EmulatorWindow::ShowEmulatorWindow(bool* is_open)
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");

        Emu* instance = Emu::Instance();
        static Emu64::UI::FileBrowser fileBrowser("Load");
        Emu64::System* system = Emu64::System::Instance();

        // Setup the window
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(550, 400), ImGuiCond_FirstUseEver);

        if (!ImGui::Begin("Emu64", is_open, NULL))
        {
            ImGui::End();
            return;
        }

        // Menu Bar
        bool showRomLoadDialog = false;
        bool closeRequested = false;
        bool emulatorShouldStop = false;
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Load ROM")) 
                    showRomLoadDialog = true;
                ImGui::Separator();
                if (ImGui::MenuItem("Exit"))
                    closeRequested = true;

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Emulator"))
            {
                if (ImGui::MenuItem("Stop Execution"))
                    emulatorShouldStop = true;
                
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        if (emulatorShouldStop)
            system->EmulatorFlags()->EmulatorShouldStop = true;
        if (closeRequested)
            instance->ControlFlags()->CloseRequested = true;

        // Handle the load dialog
        std::string romPath;
        if (fileBrowser.Render(showRomLoadDialog, romPath))
        {
            system->LoadRom((char*)romPath.c_str());
            system->EmulatorFlags()->EmulatorShouldStop = false;
            instance->ControlFlags()->EmulatorThread = std::thread(runEmulatorThread);
        }

        ImGui::End();
    }
}
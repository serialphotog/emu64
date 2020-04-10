#include "ui/emulator_window.h"

#include "imgui/imgui.h"
#include "ui/file_browser.h"

#include <string>

namespace Emu64::UI
{
    void EmulatorWindow::ShowEmulatorWindow(bool* is_open)
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");

        // Setup the file browser stuff
        static Emu64::UI::FileBrowser fileBrowser("Load");

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
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Load ROM")) 
                    showRomLoadDialog = true;

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        // Handle the load dialog
        std::string romPath;
        if (fileBrowser.Render(showRomLoadDialog, romPath))
        {
            // TODO: Load the rom into the emulator
        }

        ImGui::End();
    }

    void EmulatorWindow::ShowFileMenu()
    {
        if (ImGui::MenuItem("Load ROM")) 
            ImGui::OpenPopup("Open");

        ImGui::EndMenu();
    }
}
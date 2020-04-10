#include "ui/file_browser.h"

#include "imgui/imgui.h"

namespace Emu64::UI 
{
    FileBrowser::FileBrowser(const char* title) :
        m_title(title), m_previousVisibility(false),  m_selection(0),
        m_currentPath(std::filesystem::current_path()),
        m_currentPathIsDir(true)      
    {

    }

    static void GetFilesInPath(const std::filesystem::path& path, std::vector<File>& files)
    {
        files.clear();

        if (path.has_parent_path())
        {
            files.push_back({
                "..",
                path.parent_path()
            });
        }

        for (const std::filesystem::directory_entry& dirEntry : std::filesystem::directory_iterator(path)) 
        {
            const std::filesystem::path& dirPath = dirEntry.path();
            files.push_back({
                dirPath.filename().string(),
                dirPath
            });
        }
    }

    static const int size_t_clamp(const size_t data)
    {
        static const int max_int = std::numeric_limits<int>::max();
        return static_cast<int>(data > max_int ? max_int : data);
    }

    static bool FilesGetter(void* data, int idx, const char** out_text)
    {
        const std::vector<File>* v = reinterpret_cast<std::vector<File>*>(data);
        const int elementCount = size_t_clamp(v->size());
        if (idx < 0 || idx >= elementCount)
            return false;
        *out_text = v->at(idx).alias.data();
        return true;
    }

    const bool FileBrowser::Render(const bool isVisisble, std::string& outPath)
    {
        bool result = false;

        if (m_previousVisibility != isVisisble)
        {
            m_previousVisibility = isVisisble;
            if (isVisisble)
            {
                m_currentPath = std::filesystem::current_path();
                m_currentPathIsDir = true;

                // Get files in the current path
                GetFilesInPath(m_currentPath, m_filesInScope);
                ImGui::OpenPopup(m_title);
            }
        }

        ImVec2 initialSize = {400, 350};
        ImGui::SetNextWindowSize(initialSize, ImGuiCond_FirstUseEver);

        bool isOpen = true;
        if (ImGui::BeginPopupModal(m_title, &isOpen))
        {
            if (ImGui::ListBox("##", &m_selection, FilesGetter, &m_filesInScope, m_filesInScope.size(), 10)) 
            {
                m_currentPath = m_filesInScope[m_selection].path;
                m_currentPathIsDir = std::filesystem::is_directory(m_currentPath);

                if (m_currentPathIsDir)
                {
                    GetFilesInPath(m_currentPath, m_filesInScope);
                }
            }

            // Resize the text to popup width
            ImGui::PushItemWidth(-1);
            ImGui::TextWrapped(m_currentPath.string().data());
            ImGui::PopItemWidth();

            ImGui::Spacing();
            ImGui::SameLine(ImGui::GetWindowWidth() - 60);

            if (m_currentPathIsDir)
            {
                static const ImVec4 disabledColor = {0.3f, 0.3f, 0.3f, 1.0f};
                ImGui::PushStyleColor(ImGuiCol_Button, disabledColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, disabledColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, disabledColor);

                ImGui::Button("Select");

                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
            }
            else
            {
                if (ImGui::Button("Select"))
                {
                    ImGui::CloseCurrentPopup();
                    outPath = m_currentPath.string();
                    result = true;
                }
            }

            ImGui::EndPopup();    
        }

        return result;
    }
}
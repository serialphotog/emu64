#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace Emu64::UI
{
    const struct File
    {
        std::string alias;
        std::filesystem::path path;
    };

    class FileBrowser
    {
        public:
            explicit FileBrowser(const char* title);
            const bool Render(const bool isVisible, std::string& outPath);

        private:
            const char* m_title;
            bool m_previousVisibility;
            int m_selection;

            std::filesystem::path m_currentPath;
            bool m_currentPathIsDir;
            std::vector<File> m_filesInScope;
    };
}
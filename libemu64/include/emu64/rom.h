#pragma once

#include <string>

namespace Emu64
{
    class Rom
    {
        public:
            Rom();
            ~Rom();

            void Read(std::string path);

            unsigned char* Data() const { return m_data; }
            size_t Size() const { return m_size; }

        private:
            unsigned char* m_data;
            size_t m_size;
    };
}
#pragma once

#include <string>

namespace Emu64
{
    class Rom
    {
        public:
            Rom(unsigned char* data, size_t size);
            ~Rom();

            void ReadRom(std::string path);

            unsigned char* Data() const { return m_data; }
            size_t Size() const { return m_size; }

        private:
            unsigned char* m_data;
            size_t m_size;
    };
}
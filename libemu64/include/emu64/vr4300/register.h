#pragma once

#include <cstdint>
#include <string>

namespace Emu64::Processor
{
    class Register
    {
        public:
            Register(std::string name, uint64_t data = 0x0);

            uint64_t Data() const { return m_data; }
            void Data(const uint64_t data) { m_data = data; }

            std::string Name() const { return m_name; }
            void Name(const std::string name) { m_name = name; }

        private:
            // The data store for the register
            uint64_t m_data;

            // The name of the register
            std::string m_name;
    };
}
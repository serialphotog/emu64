#pragma once

#include <cstdint>

namespace Emu64
{
    class MemorySection
    {
        public:
            MemorySection(uint32_t offset, void* pointer);
            ~MemorySection();

            uint32_t Offset() const { return m_offset; }
            void* Pointer() const { return m_pointer; }

        private:
            uint32_t m_offset;
            void* m_pointer; // points to the physical memory
    };
}
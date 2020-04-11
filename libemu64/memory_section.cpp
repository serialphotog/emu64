#include "emu64/memory_section.h"

namespace Emu64
{
    MemorySection::MemorySection(uint32_t offset, void* pointer) :
        m_offset(offset), m_pointer(pointer)
    {

    }

    MemorySection::~MemorySection()
    {
        if (m_pointer != nullptr) delete m_pointer;
    }
}
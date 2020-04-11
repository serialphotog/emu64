#include "emu.h"

Emu* Emu::m_instance = nullptr;
Emu* Emu::Instance()
{
    if (!m_instance)
        m_instance = new Emu();
    return m_instance;
}

Emu::Emu()
{
    m_controlFlags = new ::ControlFlags();
}

Emu::~Emu()
{

}
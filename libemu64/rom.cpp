#include "emu64/rom.h"

#include <algorithm>
#include <fstream>
#include <vector>

namespace Emu64
{
    Rom::Rom()
    {

    }

    Rom::~Rom()
    {
        if (m_data != nullptr) delete m_data;
    }

    void Rom::Read(std::string path)
    {
        // TODO: Error handling!
        std::ifstream ifs(path.c_str(), std::ios::binary|std::ios::ate);
        std::ifstream::pos_type pos = ifs.tellg();
        std::vector<char> result(pos);
        ifs.seekg(0, std::ios::beg);
        ifs.read(&result[0], pos);
        std::copy(result.begin(), result.end(), m_data);
    }
}
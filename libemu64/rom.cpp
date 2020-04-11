#include "emu64/rom.h"

#include <algorithm>
#include <fstream>
#include <vector>

#include <stdio.h>

#include <iostream>

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
        FILE* fp = fopen(path.c_str(), "rb");
        if (fp == NULL)
        {
            std::cout << "[ERROR]: Failed to load ROM " << path << std::endl;
            exit(1);
        }

        fseek(fp, 0L, SEEK_END);
        m_size = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        m_data = (unsigned char*)malloc(m_size);
        fread(m_data, m_size, 1, fp);
        fclose(fp);
    }
}
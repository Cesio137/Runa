#pragma once

#include <string>
#include <fstream>

namespace Nanometro
{
class FileStream : public std::fstream
    {
    public:
        FileStream(const std::string& file);
        FileStream(const char* file);
    };
}
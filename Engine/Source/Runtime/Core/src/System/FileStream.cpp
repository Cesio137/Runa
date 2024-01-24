#include "System/FileStream.h"

Nanometro::FileStream::FileStream(const std::string& file)
    : std::fstream(file)
{

}

Nanometro::FileStream::FileStream(const char* file)
    : std::fstream(file)
{

}

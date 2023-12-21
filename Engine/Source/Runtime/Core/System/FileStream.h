#pragma once

#include <CoreMinimal.h>
#include <fstream>
#include <System/Dir.h>
#include <string>

namespace Nanometro
{
    class FileStream : public fstream
    {
    public:
        FileStream(const std::string& file);
        FileStream(const char* file);
    };
}
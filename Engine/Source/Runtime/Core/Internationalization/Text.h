#pragma once

#include <Container/String.h>
#include <cstdint>
#include <map>

namespace Nanometro
{
    class Text : public String
    {
    public:
        Text();
        Text(const std::string& str);
        Text(const char* str);

    private:
        std::map<uint8_t, std::string> msgtext;
        //void trEngineParse();
        //void trParse();
    };
}
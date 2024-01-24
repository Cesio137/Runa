#pragma once

#include <string>

namespace Nanometro
{
    class Text : public std::string
    {
    public:
        Text();
        Text(const std::string& str);
        Text(const char* str);

        std::string toUpper();
        std::string toLower();

    private:
    };
}
#include "Container/String.h"
#include <cctype>

Nanometro::String::String()
{

}

Nanometro::String::String(const std::string &str)
    : std::string(str)
{

}

Nanometro::String::String(const char* str)
    : std::string(str)
{

}

std::string Nanometro::String::toUpper()
{
    std::string str = data();
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

std::string Nanometro::String::toLower()
{
    std::string str = data();
    for (char& c : str) {
        c = tolower(c);
    }
    return str;
}







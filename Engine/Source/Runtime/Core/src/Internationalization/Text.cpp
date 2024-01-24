#include "Internationalization/Text.h"

Nanometro::Text::Text()
{

}

Nanometro::Text::Text(const std::string& str)
    : std::string(str)
{

}

Nanometro::Text::Text(const char* str)
    : std::string(str)
{

}

std::string Nanometro::Text::toUpper()
{
    std::string str = data();
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

std::string Nanometro::Text::toLower()
{
    std::string str = data();
    for (char& c : str) {
        c = tolower(c);
    }
    return str;
}

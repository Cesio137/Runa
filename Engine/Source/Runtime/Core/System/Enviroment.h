#pragma once

#include <string>
#ifndef _WIN64
#include <cstdlib>
#endif

namespace Nanometro
{
    class Enviroment
    {
    public:
        static std::string GetVariable(std::string var);
        static std::string GetUserName();

    private:

    };
}
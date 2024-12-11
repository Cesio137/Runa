#pragma once

#include <string>

namespace Runa {

    class Enviroment {
    public:
        static std::string GetVariable(std::string varname);
        static std::string GetUserName();
    };

} // Nanometro

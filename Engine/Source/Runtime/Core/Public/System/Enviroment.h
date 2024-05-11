//
// Created by natha on 10/05/2024.
//

#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <string>

namespace Nanometro {

    class Enviroment {
    public:
        static std::string GetVariable(std::string varname);
        static std::string GetUserName();
    };

} // Nanometro

#endif //ENVIROMENT_H

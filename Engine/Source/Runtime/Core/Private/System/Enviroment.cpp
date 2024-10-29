#include "System/Enviroment.h"

namespace Nanometro {
    std::string Enviroment::GetVariable(std::string varname)
    {
        std::string value;

#ifdef _WIN32
        char* varbuffer = nullptr;
        size_t size = 0;
        if (_dupenv_s(&varbuffer, &size, varname.c_str()) == 0 && varbuffer != nullptr)
        {
            value = varbuffer;
            free(varbuffer);
            return value;
        }

#else
        value = std::getenv(varname.c_str());
        return value;
#endif

        return "";
    }

    std::string Enviroment::GetUserName()
    {
#ifdef _WIN64
        return GetVariable("USERNAME");
#else
        return GetVariable("HOSTNAME");
#endif

        return "";
    }
} // Nanometro
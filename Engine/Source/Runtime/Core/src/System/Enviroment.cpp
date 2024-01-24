#include "System/Enviroment.h"

std::string Nanometro::Enviroment::GetVariable(std::string varname)
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

std::string Nanometro::Enviroment::GetUserName()
{
#ifdef _WIN64
    return GetVariable("USERNAME");
#else
    return GetVariable("HOSTNAME");
#endif

    return "";
}

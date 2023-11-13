#include "Enviroment.h"

String Enviroment::GetVariable(String varname)
{
    String value;
	char* varbuffer = nullptr;
	size_t size = 0;

    if (_dupenv_s(&varbuffer, &size, varname.c_str()) == 0 && varbuffer != nullptr)
    {
        value = varbuffer;
        free(varbuffer);
        return value;
    }

    return "";
}

String Enviroment::GetUserName()
{
#ifdef HOST_SYSTEM_WINDOWS
    return GetVariable("USERNAME");
#else
    return GetVariable("HOSTNAME");
#endif

    return "";
}

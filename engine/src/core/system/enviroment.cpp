#include "core/system/enviroment.h"

namespace Runa::System {
    eastl::string GetVariable(const char *varname) {
        eastl::string value;

#ifdef _WIN64
        char *varbuffer = nullptr;
        size_t size = 0;
        if (_dupenv_s(&varbuffer, &size, varname) == 0 && varbuffer != nullptr) {
            value = varbuffer;
            free(varbuffer);
            return value;
        }

#else
        value = std::getenv(varname);
        return value;
#endif

        return "";
    }

    eastl::string GetUserName() {
#ifdef _WIN64
        return GetVariable("USERNAME");
#else
        return GetVariable("HOSTNAME");
#endif

        return "";
    }
} // Nanometro

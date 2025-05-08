#pragma once

#include <EASTL/string.h>

namespace Runa::System {
    eastl::string GetVariable(const char *varname);

    eastl::string GetUserName();
}

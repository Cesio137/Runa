#pragma once

#include <string>

namespace runa::utils {
    std::string get_env_var(const char *varname);
    std::string get_user_name();
}

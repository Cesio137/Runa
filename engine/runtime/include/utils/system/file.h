#pragma once

#include <string>
#include <vector>

namespace runa::utils::file {
    std::vector<uint8_t> load_file(const std::string &filepath);
    std::string load_text_file(const std::string &filepath);
    bool file_exist(const std::string &filepath);
}

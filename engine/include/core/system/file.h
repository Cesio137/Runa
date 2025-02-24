#pragma once

#include <string>
#include <vector>
#ifndef _WIN64
#include <cstdint>
#endif

namespace Runa::System {
    std::vector<uint8_t> LoadFileToBuffer(const std::string &filepath);

    std::string LoadFileToString(const std::string &filepath);

    bool FileExists(const std::string &filepath);
}

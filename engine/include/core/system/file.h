#pragma once

#include <EASTL/string.h>
#include <EASTL/vector.h>
#ifndef _WIN64
#include <cstdint>
#endif

namespace Runa::System {
    eastl::vector<uint8_t> LoadFileToBuffer(const char *filepath);

    eastl::string LoadFileToString(const char *filepath);

    bool FileExists(const char *filepath);
}

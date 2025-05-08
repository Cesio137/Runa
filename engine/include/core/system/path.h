#pragma once

#include <EASTL/string.h>

namespace Runa::System {
    eastl::string NativeSeparator(const char *dir);

    eastl::string HomeDir();

    eastl::string AppDataDir();

    eastl::string DesktopDir();

    eastl::string DownloadDir();

    eastl::string DocumentsDir();

    eastl::string GameContentDir();

    eastl::string CurrentDir();

    eastl::string GetAsset(const char *dir);
}

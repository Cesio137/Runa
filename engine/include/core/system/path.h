#pragma once

#include <string>

namespace Runa::System {
    std::string NativeSeparator(const std::string &dir);

    std::string HomeDir();

    std::string AppDataDir();

    std::string DesktopDir();

    std::string DownloadDir();

    std::string DocumentsDir();

    std::string GameContentDir();

    std::string CurrentDir();

    std::string GetAsset(const std::string &dir);
}

#pragma once

#include <string>

namespace Runa {

    class Path {
    public:
        static std::string nativeSeparator(std::string dir);
        static std::string HomeLocation();
        static std::string AppDataLocation();
        static std::string DesktopLocation();
        static std::string DownloadLocation();
        static std::string DocumentsLocation();
        static std::string GameContentLocation();
        static std::string GetAsset(std::string dir);
    };

} // Nanometro

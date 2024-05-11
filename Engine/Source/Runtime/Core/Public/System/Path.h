#pragma once

#ifndef PATH_H
#define PATH_H

#include <string>

namespace Nanometro {

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

#endif //PATH_H

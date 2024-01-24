#pragma once

#include "System/Enviroment.h"
#include <filesystem>

namespace Nanometro
{
    class Path : public std::filesystem::path
    {
    public:
        Path();

        static std::string nativeSeparator(std::string dir);
        static std::string HomeLocation();
        static std::string AppDataLocation();
        static std::string DesktopLocation();
        static std::string DownloadLocation();
        static std::string DocumentsLocation();
        static std::string GameContentLocation();
        static std::string GetAsset(std::string dir);

    };
}
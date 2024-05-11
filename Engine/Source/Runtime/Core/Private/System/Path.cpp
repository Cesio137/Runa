//
// Created by natha on 10/05/2024.
//

#include "System/Path.h"
#include <filesystem>
#include "System/Enviroment.h"

namespace Nanometro {
    std::string Path::nativeSeparator(std::string dir)
    {
        if (dir.empty())
            return "";

        std::filesystem::path directory(dir.c_str());

        return directory.make_preferred().string();
    }

    std::string Path::HomeLocation()
    {
        std::string path;

#ifdef _WIN64
        if (!Enviroment::GetVariable("USERPROFILE").empty())
        {
            path = Enviroment::GetVariable("USERPROFILE");
        }
#else
        if (!Enviroment::GetVariable("HOME").empty())
        {
            path = Enviroment::GetVariable("HOME");
        }
#endif

        return  path;
    }

    std::string Path::AppDataLocation()
    {
        std::string path;

#ifdef _WIN32
        if (!Enviroment::GetVariable("APPDATA").empty())
        {
            path = Enviroment::GetVariable("APPDATA");
        }
#else
        if (!HomeLocation().empty())
        {
            path = HomeLocation() + nativeSeparator("/.local/share");
        }
#endif

        return  path;
    }

    std::string Path::DesktopLocation()
    {
        if (!HomeLocation().empty())
        {
            return HomeLocation() + nativeSeparator("/Desktop");
        }
        return "";
    }

    std::string Path::DownloadLocation()
    {
        if (!HomeLocation().empty())
        {
            return HomeLocation() + nativeSeparator("/Downloads");
        }
        return "";
    }

    std::string Path::DocumentsLocation()
    {
        if (!HomeLocation().empty())
        {
            return HomeLocation() + nativeSeparator("/Documents");
        }
        return "";
    }

    std::string Path::GameContentLocation()
    {
        return std::filesystem::current_path().string() + nativeSeparator("Game/Content");
    }

    std::string Path::GetAsset(std::string dir)
    {
        std::string asset = GameContentLocation();
        if (!dir.starts_with("/") || !dir.starts_with("\\"))
        {
            asset.append(nativeSeparator("/"));
        }
        asset.append(nativeSeparator(dir));
        return asset;
    }
} // Nanometro
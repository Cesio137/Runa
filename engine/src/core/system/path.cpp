#include "core/system/path.h"
#include "core/system/enviroment.h"
#include <filesystem>

namespace Runa::System {
    std::string NativeSeparator(const std::string &dir) {
        if (dir.empty())
            return "";

        std::filesystem::path directory(dir.c_str());

        return directory.make_preferred().string();
    }

    std::string HomeDir() {
        std::string path;

#ifdef _WIN64
        if (!GetVariable("USERPROFILE").empty()) {
            path = GetVariable("USERPROFILE");
        }
#else
        if (!GetVariable("HOME").empty())
        {
            path = GetVariable("HOME");
        }
#endif

        return path;
    }

    std::string AppDataDir() {
        std::string path;

#ifdef _WIN64
        if (!GetVariable("APPDATA").empty()) {
            path = GetVariable("APPDATA");
        }
#else
        if (!HomeLocation().empty())
        {
            path = HomeLocation() + NativeSeparator("/.local/share");
        }
#endif

        return path;
    }

    std::string DesktopDir() {
        if (!HomeDir().empty()) {
            return HomeDir() + NativeSeparator("/Desktop");
        }
        return "";
    }

    std::string DownloadDir() {
        if (!HomeDir().empty()) {
            return HomeDir() + NativeSeparator("/Downloads");
        }
        return "";
    }

    std::string DocumentsDir() {
        if (!HomeDir().empty()) {
            return HomeDir() + NativeSeparator("/Documents");
        }
        return "";
    }

    std::string GameContentDir() {
        return std::filesystem::current_path().string() + NativeSeparator("Game/Content");
    }

    std::string CurrentDir()
    {
        return std::filesystem::current_path().string();
    }

    std::string GetAsset(const std::string &dir)
    {
        std::string asset = GameContentDir();
        if (!dir.starts_with("/") || !dir.starts_with("\\")) {
            asset.append(NativeSeparator("/"));
        }
        asset.append(NativeSeparator(dir));
        return asset;
    }
} // Nanometro

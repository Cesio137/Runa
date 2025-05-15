#include "core/system/path.h"
#include "core/system/enviroment.h"
#include <filesystem>
#include <SDL3/SDL.h>

#if defined(_WIN32) || defined(_WIN64)
    constexpr char PATH_SEPARATOR = '\\';
    constexpr char PATH_SEPARATOR_OTHER = '/';
    constexpr const char* PATH_SEPARATOR_STR = "\\";
#else
    constexpr char PATH_SEPARATOR = '/';
    constexpr char PATH_SEPARATOR_OTHER = '\\';
    constexpr const char* PATH_SEPARATOR_STR = "/";
#endif


namespace Runa::System {
    eastl::string NativeSeparator(const char *dir) {
        if (dir == nullptr || *dir == '\0')
            return "";

        std::filesystem::path directory(dir);

        return directory.make_preferred().string().c_str();
    }

    eastl::string HomeDir() {
       eastl::string path = "";

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

    eastl::string AppDataDir() {
        eastl::string path;

#ifdef _WIN64
        if (!GetVariable("APPDATA").empty()) {
            path = GetVariable("APPDATA");
        }
#else
        if (!HomeDir().empty())
        {
            path = HomeDir() + NativeSeparator("/.local/share");
        }
#endif

        return path;
    }

    eastl::string DesktopDir() {
        if (!HomeDir().empty()) {
            return HomeDir() + NativeSeparator("/Desktop");
        }
        return "";
    }

    eastl::string DownloadDir() {
        if (!HomeDir().empty()) {
            return HomeDir() + NativeSeparator("/Downloads");
        }
        return "";
    }

    eastl::string DocumentsDir() {
        if (!HomeDir().empty()) {
            return HomeDir() + NativeSeparator("/Documents");
        }
        return "";
    }

    eastl::string GameContentDir() {
        const char *base_path = SDL_GetBasePath();

        return base_path + NativeSeparator("Game/Content");
    }

    eastl::string CurrentDir() {
        return SDL_GetBasePath();
    }

    eastl::string GetAsset(const char *dir) {
        eastl::string asset = GameContentDir();
        if (dir[0] == '/' || dir[0] == '\\') {
            asset.append(NativeSeparator("/"));
        }
        asset.append(NativeSeparator(dir));
        return asset;
    }
} // Nanometro

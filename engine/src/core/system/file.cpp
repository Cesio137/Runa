#include "core/system/file.h"
#include "core/system/path.h"
#include <SDL3/SDL.h>
#include <EASTL/unique_ptr.h>

namespace Runa::System {
    eastl::vector<uint8_t> LoadFileToBuffer(const char *filepath) {
        eastl::vector<uint8_t> buffer;

        eastl::unique_ptr<SDL_IOStream, decltype(&SDL_CloseIO)> file(SDL_IOFromFile(filepath, "rb"), SDL_CloseIO);
        if (!file) {
            SDL_Log("Error loading file to buffer: Unable to open file '%s': %s", filepath, SDL_GetError());
            return buffer;
        }

        Sint64 filesize;
        if (SDL_SeekIO(file.get(), 0, SDL_IO_SEEK_END) < 0) {
            SDL_Log("Error loading file to buffer: Unable to seek to end of file '%s': %s", filepath, SDL_GetError());
            return buffer;
        }

        filesize = SDL_TellIO(file.get());
        if (filesize < 0) {
            SDL_Log("Error loading file to buffer: Unable to determine size of file '%s': %s", filepath, SDL_GetError());
            return buffer;
        }

        if (SDL_SeekIO(file.get(), 0, SDL_IO_SEEK_SET) < 0) {
            SDL_Log("Error loading file to buffer: Unable to seek to beginning of file '%s': %s", filepath, SDL_GetError());
            return buffer;
        }

        buffer.resize(filesize);

        if (filesize > 0) {
            size_t bytesread = SDL_ReadIO(file.get(), buffer.data(), filesize);
            if (bytesread < filesize) {
                SDL_Log("Warning: Only read %zu of %lld bytes from file '%s'", bytesread, filesize, filepath);
                buffer.resize(bytesread);
            }
        }

        file.reset();

        return buffer;
    }

    eastl::string LoadFileToString(const char *filepath) {
        eastl::string content;

        eastl::unique_ptr<SDL_IOStream, decltype(&SDL_CloseIO)> file(SDL_IOFromFile(filepath, "rb"), SDL_CloseIO);
        if (!file) {
            SDL_Log("Error loading file to string: Unable to open file '%s': %s", filepath, SDL_GetError());
            return content;
        }

        if (SDL_SeekIO(file.get(), 0, SDL_IO_SEEK_END) < 0) {
            SDL_Log("Error loading file to string: Unable to seek to end of file '%s': %s", filepath, SDL_GetError());
            return content;
        }

        Sint64 filesize = SDL_TellIO(file.get());
        if (filesize < 0) {
            SDL_Log("Error loading file to string: Unable to determine size of file '%s': %s", filepath, SDL_GetError());
            return content;
        }

        if (SDL_SeekIO(file.get(), 0, SDL_IO_SEEK_SET) < 0) {
            SDL_Log("Error loading file to string: Unable to seek to beginning of file '%s': %s", filepath, SDL_GetError());
            return content;
        }

        content.resize(filesize);

        if (filesize > 0) {
            size_t bytesread = SDL_ReadIO(file.get(), &content[0], filesize);
            if (bytesread < filesize) {
                SDL_Log("Warning: Only read %zu of %lld bytes from file '%s'", bytesread, filesize, filepath);
                content.resize(bytesread);
            }
        }

        file.reset();

        return content;
    }

    bool FileExists(const char *filepath) {
        if (filepath == nullptr || *filepath == '\0') {
            SDL_Log("Error checking file existence: Invalid filepath (null or empty)");
            return false;
        }

        SDL_IOStream* file = SDL_IOFromFile(filepath, "rb");

        if (file) {
            SDL_CloseIO(file);
            return true;
        }

        // No need to log here as file not existing is often an expected case
        return false;
    }
}
#include "core/system/file.h"
#include <stdint.h>
#include <SDL3/SDL.h>

char *runaLoadFile(const char *filepath) {
    if (filepath == NULL || *filepath == '\0') {
        SDL_Log("Error checking file existence: Invalid filepath (null or empty)");
        return 0;
    }

    SDL_IOStream *file = SDL_IOFromFile(filepath, "rb");
    if (!file) {
        SDL_Log("Error loading file to string: Unable to open file '%s': %s", filepath, SDL_GetError());
        return "";
    }

    if (SDL_SeekIO(file, 0, SDL_IO_SEEK_END) < 0) {
        SDL_Log("Error loading file to string: Unable to seek to end of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        return "";
    }

    Sint64 filesize = SDL_TellIO(file);
    if (filesize < 0) {
        SDL_Log("Error loading file to string: Unable to determine size of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        return "";
    }

    if (SDL_SeekIO(file, 0, SDL_IO_SEEK_SET) < 0) {
        SDL_Log("Error loading file to string: Unable to seek to beginning of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        return "";
    }

    char *buffer = SDL_malloc(filesize + 1);
    if (!buffer) {
        SDL_Log("Error loading file to string: Out of memory for file '%s'", filepath);
        SDL_CloseIO(file);
        return "";
    }

    size_t bytes_read = SDL_ReadIO(file, buffer, filesize);
    SDL_CloseIO(file);

    if (bytes_read != filesize) {
        SDL_Log("Error loading file to string: Read only %zu bytes of %lld from file '%s': %s",
                bytes_read, filesize, filepath, SDL_GetError());
        SDL_free(buffer);
        return "";
    }

    buffer[filesize] = '\0';

    return buffer;
}

int runaFileExist(const char *filepath) {
    if (filepath == NULL || *filepath == '\0') {
        SDL_Log("Error checking file existence: Invalid filepath (null or empty)");
        return 0;
    }

    SDL_IOStream *file = SDL_IOFromFile(filepath, "rb");

    if (file) {
        SDL_CloseIO(file);
        return 1;
    }

    // No need to log here as file not existing is often an expected case
    return 0;
}

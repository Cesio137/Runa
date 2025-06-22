#include "utils/system/file.h"
#include <SDL3/SDL.h>

vec_uint8 runaLoadFile(const char *filepath) {
    vec_uint8 buffer = vec_uint8_init();
    if (filepath == NULL || *filepath == '\0') {
        SDL_Log("Error checking file existence: Invalid filepath (null or empty)");
        vec_uint8_drop(&buffer);
        return buffer;
    }

    SDL_IOStream *file = SDL_IOFromFile(filepath, "rb");
    if (!file) {
        SDL_Log("Error loading file to string: Unable to open file '%s': %s", filepath, SDL_GetError());
        vec_uint8_drop(&buffer);
        return buffer;
    }

    if (SDL_SeekIO(file, 0, SDL_IO_SEEK_END) < 0) {
        SDL_Log("Error loading file to string: Unable to seek to end of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        vec_uint8_drop(&buffer);
        return buffer;
    }

    Sint64 filesize = SDL_TellIO(file);
    if (filesize < 0) {
        SDL_Log("Error loading file to string: Unable to determine size of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        vec_uint8_drop(&buffer);
        return buffer;
    }

    if (SDL_SeekIO(file, 0, SDL_IO_SEEK_SET) < 0) {
        SDL_Log("Error loading file to string: Unable to seek to beginning of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        vec_uint8_drop(&buffer);
        return buffer;
    }

    //char *buffer = SDL_malloc(filesize + 1);
    if (!vec_uint8_reserve(&buffer, filesize)) {
        SDL_Log("Error loading file to string: Out of memory for file '%s'", filepath);
        SDL_CloseIO(file);
        vec_uint8_drop(&buffer);
        return buffer;
    }

    size_t bytes_read = SDL_ReadIO(file, buffer.data, filesize);
    SDL_CloseIO(file);

    if (bytes_read != filesize) {
        SDL_Log("Error loading file to string: Read only %zu bytes of %lld from file '%s': %s",
                bytes_read, filesize, filepath, SDL_GetError());
        vec_uint8_drop(&buffer);
        return buffer;
    }

    return buffer;
}

cstr runaLoadTextFile(const char *filepath) {
    cstr text = cstr_init();
    if (filepath == NULL || *filepath == '\0') {
        SDL_Log("Error checking file existence: Invalid filepath (null or empty)");
        cstr_drop(&text);
        return text;
    }

    SDL_IOStream *file = SDL_IOFromFile(filepath, "rb");
    if (!file) {
        SDL_Log("Error loading file to string: Unable to open file '%s': %s", filepath, SDL_GetError());
        cstr_drop(&text);
        return text;
    }

    if (SDL_SeekIO(file, 0, SDL_IO_SEEK_END) < 0) {
        SDL_Log("Error loading file to string: Unable to seek to end of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        cstr_drop(&text);
        return text;
    }

    Sint64 filesize = SDL_TellIO(file);
    if (filesize < 0) {
        SDL_Log("Error loading file to string: Unable to determine size of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        cstr_drop(&text);
        return text;
    }

    if (SDL_SeekIO(file, 0, SDL_IO_SEEK_SET) < 0) {
        SDL_Log("Error loading file to string: Unable to seek to beginning of file '%s': %s", filepath, SDL_GetError());
        SDL_CloseIO(file);
        cstr_drop(&text);
        return text;
    }

    unsigned char *buffer = SDL_malloc(filesize + 1);
    if (!buffer) {
        SDL_Log("Error loading file to string: Out of memory for file '%s'", filepath);
        SDL_CloseIO(file);
        cstr_drop(&text);
        return text;
    }


    size_t bytes_read = SDL_ReadIO(file, buffer, filesize);
    SDL_CloseIO(file);

    if (bytes_read != filesize) {
        SDL_Log("Error loading file to string: Read only %zu bytes of %lld from file '%s': %s",
                bytes_read, filesize, filepath, SDL_GetError());
        SDL_free(buffer);
        return text;
    }

    cstr_assign(&text, buffer);
    return text;
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

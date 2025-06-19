#include "core/system/path.h"
#include "core/system/environment.h"
#include <SDL3/SDL.h>

#ifdef _WIN64
const char PATH_SEPARATOR = '\\';
const char PATH_SEPARATOR_OTHER = '/';
const char *PATH_SEPARATOR_STR = "\\";
#else
const char PATH_SEPARATOR = '/';
const char PATH_SEPARATOR_OTHER = '\\';
const const char* PATH_SEPARATOR_STR = "/";
#endif


char *runaJoinPaths(const char *paths[], const size_t len) {
    if (len > 0 && paths == NULL) {
        SDL_Log("Paths array is NULL");
        return NULL;
    }

    // Strs to concat
    char **srcs = SDL_malloc(len * sizeof(char*));
    if (srcs == NULL) {
        SDL_Log("Failed to allocate memory for filtered strs");
        return NULL;
    }

    // Initialize all pointers with null
    for (size_t i = 0; i < len; i++) {
        srcs[i] = NULL;
    }

    size_t valid_paths = 0;

    // Filter str
    for (size_t i = 0; i < len; i++) {
        const char *str = paths[i];
        if (str == NULL || SDL_strlen(str) == 0) continue;

        size_t str_len = SDL_strlen(str);
        int add_separator = (str_len > 0 && str[str_len-1] != PATH_SEPARATOR && str[str_len-1] != PATH_SEPARATOR_OTHER) ? 1 : 0;

        char *src = SDL_malloc(add_separator ? str_len + 2 : str_len + 1);
        if (src == NULL) {
            for (size_t j = 0; j < len; j++) {
                SDL_free(srcs[j]);
            }
            SDL_free(srcs);
            SDL_Log("Failed to allocate memory for str filter");
            return NULL;
        }
        // Init str
        src[0] = '\0';

        int was_separator = 0;
        for (size_t i_char = 0; i_char < str_len; i_char++) {
            char c = str[i_char];

            if (i_char == 0 && (c == PATH_SEPARATOR || c == PATH_SEPARATOR_OTHER)) {
                was_separator = 1;
                continue;
            }

            if (c == PATH_SEPARATOR || c == PATH_SEPARATOR_OTHER) {
                if (was_separator) continue;
                was_separator = 1;
                c = PATH_SEPARATOR;
            } else {
                was_separator = 0;
            }
            // Add char by char
            char temp[2] = {c, '\0'};
            SDL_strlcat(src, temp, str_len + 1);
        }

        if (add_separator) SDL_strlcat(src, PATH_SEPARATOR_STR, str_len + 2);

        srcs[i] = src;
        valid_paths++;
    }

    size_t buf_size = 0;
    for (size_t i = 0; i < len; i++) {
        if (srcs[i] != NULL) {
            buf_size += SDL_strlen(srcs[i]);
        }
    }

    if (buf_size == 0) {
        // Free all memory if buf_size is 0
        for (size_t i = 0; i < len; i++) {
            SDL_free(srcs[i]);
        }
        SDL_free(srcs);
        return NULL;
    }

    buf_size += 1; // For \0

    char *buf = SDL_malloc(buf_size);
    if (buf == NULL) {
        // Free memory
        for (size_t i = 0; i < len; i++) {
            SDL_free(srcs[i]);
        }
        SDL_free(srcs);
        SDL_Log("Failed to allocate memory for path concatenation");
        return NULL;
    }

    // Initialize str
    buf[0] = '\0';

    for (size_t i = 0; i < len; i++) {
        if (srcs[i] != NULL) {
            SDL_strlcat(buf, srcs[i], buf_size);
        }
    }

    // Free 'srcs' var memory
    for (size_t i = 0; i < len; i++) {
        SDL_free(srcs[i]);
    }
    SDL_free(srcs);

    return buf;
}

char *runaNativeSeparator(const char *path) {
    if (path == NULL) {
        return NULL;
    }

    size_t len = SDL_strlen(path);
    char *new_path = (char *) malloc(len + 1);
    if (new_path == NULL) {
        SDL_Log("Failed to allocate memory for path conversion");
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (path[i] == PATH_SEPARATOR_OTHER) {
            new_path[i] = PATH_SEPARATOR;
        } else {
            new_path[i] = path[i];
        }
    }

    new_path[len] = '\0';

    return new_path;
}

const char *runaHomeDir() {
    const char *path = NULL;
#ifdef _WIN64
    path = runaGetEnvVar("USERPROFILE");
    if (!path) {
        SDL_Log("Failed to get home directory");
        return NULL;
    }
#else
    path = runaGetEnvVar("HOME");
    if (!path) {
        SDL_Log("Failed to get home directory");
        return NULL;
    }
#endif
    return path;
}

char *runaGetPrefPath(const char *org, const char *app) {
    char *path = SDL_GetPrefPath(org, app);
    if (!path) {
        SDL_Log("Failed to get pref path");
        return NULL;
    }
    return path;
}

const char *CurrentDir() {
    return SDL_GetBasePath();
}

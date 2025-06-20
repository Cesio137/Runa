#include "utils/system/path.h"
#include "utils/system/environment.h"
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


cstr runaJoinPaths(const vec_cstr paths) {
    if (paths.size == 0) {
        SDL_Log("Paths array is NULL");
        return cstr_init();
    }

    cstr joined_path = cstr_init();

    c_foreach(p, vec_cstr, paths) {
        const cstr src = *p.ref;
        if (cstr_is_empty(&src)) {
            cstr_drop(&src);
            continue;
        }
        
        cstr dest = cstr_init();
        
        const isize src_size = cstr_size(&src);
        const char *raw_src = cstr_str(&src);
        int was_separator = 0;
        for (isize i = 0; i < src_size; i++) {
            const c = raw_src[i];
            if (i == 0 && (c == PATH_SEPARATOR || c == PATH_SEPARATOR_OTHER)) {
               was_separator = 1;
               continue;
            }
            if (c == PATH_SEPARATOR || c == PATH_SEPARATOR_OTHER) {
                if (was_separator) continue;
                was_separator = 1;
                cstr_push(&dest, PATH_SEPARATOR_STR);
            } else {
                was_separator = 0;
                const char temp[2] = {c, '\0'};
                cstr_push(&dest, temp);
            }
        }
        if (!cstr_ends_with(&dest, PATH_SEPARATOR_STR)) {
            cstr_push(&dest, PATH_SEPARATOR_STR);
        }
        cstr_append_s(&joined_path, dest);
        cstr_drop(&dest);
    }

    return joined_path;
}

cstr runaNativeSeparator(const char *path) {
    if (path == NULL) {
        return cstr_init();
    }

    size_t len = SDL_strlen(path);

    cstr new_path = cstr_init();
    for (size_t i = 0; i < len; i++) {
        if (path[i] == PATH_SEPARATOR_OTHER) {
            cstr_push(&new_path, PATH_SEPARATOR_STR);
        } else {
            char temp[2] = {path[i], '\0'}; // Corrigido: cast inválido para char*
            cstr_push(&new_path, temp);
        }
    }

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

cstr runaGetPrefPath(const char *org, const char *app) {
    char *path = SDL_GetPrefPath(org, app);
    if (!path) {
        SDL_Log("Failed to get pref path");
        return cstr_init();
    }
    return cstr_from(path);
}

const char *CurrentDir() {
    return SDL_GetBasePath();
}


#include "utils/system/environment.h"
#include <SDL3/SDL.h>

const char *runaGetEnvVar(const char *varname) {
    SDL_Environment *env = SDL_GetEnvironment();
    if (!env) {
        SDL_Log("Error getting environment variable: %s", SDL_GetError());
        return "";
    }
    const char *val = SDL_GetEnvironmentVariable(env, varname);
    if (!val) {
        SDL_Log("Error getting environment variable: Value is null");
        return "";
    }
    return val;
}

const char *runaGetUserName() {
#ifdef _WIN64
    return runaGetEnvVar("USERNAME");
#else
    return runaGetEnvVar("HOSTNAME");
#endif

    return "";
}

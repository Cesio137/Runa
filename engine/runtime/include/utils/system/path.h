#pragma once

#include <container/cvector.h>

#ifdef __cplusplus
extern "C" {
#endif

cstr runaJoinPaths(const vec_cstr paths);
cstr runaNativeSeparator(const char *path);
const char *runaGetHomeDir();
cstr runaGetPrefPath(const char *org, const char *app);
const char* runaCurrentDir();

#ifdef __cplusplus
}
#endif

//eastl::string GameContentDir();

//eastl::string GetAsset(const char *dir);

#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

char *runaJoinPaths(const char *paths[], const size_t len);
char *runaNativeSeparator(const char *path);
const char *runaGetHomeDir();
char *runaGetPrefPath(const char *org, const char *app);

#ifdef __cplusplus
}
#endif

//eastl::string GameContentDir();

//const char *CurrentDir();

//eastl::string GetAsset(const char *dir);

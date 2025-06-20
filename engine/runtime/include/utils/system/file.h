#pragma once

#include <container/cvector.h>

#ifdef __cplusplus
extern "C" {
#endif

vec_uint8 runaLoadFile(const char *filepath);
cstr runaLoadTextFile(const char *filepath);
int runaFileExist(const char *filepath);

#ifdef __cplusplus
}
#endif

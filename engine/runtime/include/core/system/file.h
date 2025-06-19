#pragma once

#ifndef _WIN64
#include <cstdint>
#endif

#ifdef __cplusplus
extern "C" {
#endif

char *runaLoadFile(const char *filepath);
int runaFileExist(const char *filepath);

#ifdef __cplusplus
}
#endif

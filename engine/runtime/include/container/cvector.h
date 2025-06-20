#pragma once

#include <stc/common.h>

// Unsigned char buffer
#define i_key uint8
#define i_use_cmp // enable sorting/searching using default <, == operators
#include <stc/vec.h>
#undef i_key
#undef i_use_cmp

// Vec of str
#include "container/cstring.h"
#define i_keypro cstr
#include <stc/vec.h>
#undef i_keypro
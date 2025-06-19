#pragma once

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
    GLenum type;
} gl_texture_t;

int runaGenTexture(gl_texture_t *gl_texture, const char *textdir, const GLenum textype, const GLenum slot,
                   const GLenum format, GLenum pixeltype);
void runaDeleteTexture(gl_texture_t *gl_texture);
void runaBindTexture(gl_texture_t *gl_texture);
void runaUnbindTexture(gl_texture_t *gl_texture);



#ifdef __cplusplus
}
#endif
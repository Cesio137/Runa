#pragma once

#include "shaders/glshader.h"
#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
    GLenum type;
} gl_texture_t;

int gl_GenTexture(gl_texture_t *gl_texture, const char *texturefile, const GLenum textype, const GLenum slot,
                   const GLenum format, GLenum pixeltype);
void gl_DeleteTexture(gl_texture_t *gl_texture);
void gl_BindTexture(gl_texture_t *gl_texture);
void gl_UnbindTexture(gl_texture_t *gl_texture);

#ifdef __cplusplus
}
#endif
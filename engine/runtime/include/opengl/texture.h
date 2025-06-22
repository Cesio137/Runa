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

int runaGenTexture(gl_texture_t *gl_texture, const char *texturefile, const GLenum textype, const GLenum slot,
                   const GLenum format, GLenum pixeltype);
void runaDeleteTexture(gl_texture_t *gl_texture);
void runaBindTexture(gl_texture_t *gl_texture);
void runaUnbindTexture(gl_texture_t *gl_texture);
void runaSetUniformLocation(gl_shader_t *shader, const char *uniform, const GLuint unit);



#ifdef __cplusplus
}
#endif
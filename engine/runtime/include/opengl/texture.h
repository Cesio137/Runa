#pragma once

#include <glad/glad.h>

typedef struct {
    GLuint id;
    GLenum type;
}gl_texture_t;

int runa_glGenTexture(gl_texture_t *gl_texture, const char *textdir, const GLenum textype, const GLenum slot, const GLenum format, GLenum pixeltype);
void runa_glDeleteTexture(gl_texture_t *gl_texture);
void runa_glBindTexture(gl_texture_t *gl_texture);
void runa_glUnbindTexture(gl_texture_t *gl_texture);
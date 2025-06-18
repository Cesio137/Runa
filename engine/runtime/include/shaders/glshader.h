#pragma once

#include <glad/glad.h>

typedef struct {
    GLuint id;
}gl_shader_t;

int runa_glCreateShader(gl_shader_t *shader, char *vertexfile, const char *fragmentfile);
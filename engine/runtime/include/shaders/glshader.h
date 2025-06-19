#pragma once

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
} gl_shader_t;

int runaCreateShaderProgram(gl_shader_t *gl_shader, const char *vertexfile, const char *fragmentfile);

void runaDeleteShaderProgram(gl_shader_t *gl_shader);

void runaUseShaderProgram(gl_shader_t *gl_shader);

#ifdef __cplusplus
}
#endif

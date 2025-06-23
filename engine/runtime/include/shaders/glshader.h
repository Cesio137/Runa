#pragma once

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
} gl_shader_t;

int gl_CreateShaderProgram(gl_shader_t *gl_shader, const char *vertexfile, const char *fragmentfile);
void gl_DeleteShaderProgram(gl_shader_t *gl_shader);
void gl_UseShaderProgram(gl_shader_t *gl_shader);
void gl_SetUniformLocation(gl_shader_t *shader, const char *uniform, const GLuint unit);

#ifdef __cplusplus
}
#endif

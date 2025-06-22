#pragma once

#include "opengl/vertex_buffer.h"
#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
} gl_vertex_array_t;

void runaGenVertexArray(gl_vertex_array_t *vertex_array);
void runaDeleteVertexArray(gl_vertex_array_t *vertex_array);
void runaBindVertexArray(gl_vertex_array_t *vertex_array);
void runaUnbindVertexArray();
void runaEnableVertexAttribArray(gl_vertex_buffer_t *vertex_buffer, const GLuint layout, GLuint num, GLenum type,
                                 GLsizeiptr stride, void *offset);

#ifdef __cplusplus
}
#endif
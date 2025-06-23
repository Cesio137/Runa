#pragma once

#include "opengl/vertex_buffer.h"
#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
} gl_vertex_array_t;

void gl_GenVertexArray(gl_vertex_array_t *vertex_array);
void gl_DeleteVertexArray(gl_vertex_array_t *vertex_array);
void gl_BindVertexArray(gl_vertex_array_t *vertex_array);
void gl_UnbindVertexArray();
void gl_EnableVertexAttribArray(gl_vertex_buffer_t *vertex_buffer, const GLuint layout, GLuint num, GLenum type,
                                 GLsizeiptr stride, void *offset);

#ifdef __cplusplus
}
#endif
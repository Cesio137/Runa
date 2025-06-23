#pragma once

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
} gl_vertex_buffer_t;

void gl_GenVertexBuffer(gl_vertex_buffer_t *vertex_buffer, const GLfloat *vertices, const GLsizeiptr size);
void gl_DeleteVertexBuffer(gl_vertex_buffer_t *vertex_buffer);
void gl_BindVertexBuffer(gl_vertex_buffer_t *vertex_buffer);
void gl_UnbindVertexBuffer();

#ifdef __cplusplus
}
#endif
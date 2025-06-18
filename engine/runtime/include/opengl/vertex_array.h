#pragma once

#include "opengl/vertex_buffer.h"
#include <glad/glad.h>

typedef struct {
    GLuint id;
}gl_vertex_array_t;

void runa_glGenVertexArray(gl_vertex_array_t *vertex_array, const GLfloat *vertices, const GLsizeiptr size);
void runa_glDeleteVertexArray(gl_vertex_array_t *vertex_array);
void runa_glBindBuffer(gl_vertex_array_t *vertex_array);
void runa_glUnbindBuffer();
void runa_EnableVertexAttribArray(gl_vertex_array_t *vertex_array, gl_vertex_buffer_t *vertex_buffer, const GLuint layout, GLuint num, GLenum type, GLsizeiptr stride, void* offset);
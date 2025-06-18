#pragma once

#include <glad/glad.h>

typedef struct {
    GLuint id;
}gl_vertex_buffer_t;

void runa_glGenBuffer(gl_vertex_buffer_t *vertex_buffer, const GLfloat *vertices, const GLsizeiptr size);
void runa_glDeleteBuffer(gl_vertex_buffer_t *vertex_buffer);
void runa_glBindBuffer(gl_vertex_buffer_t *vertex_buffer);
void runa_glUnbindBuffer();
#pragma once

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
} gl_vertex_buffer_t;

void runaGenBuffer(gl_vertex_buffer_t *vertex_buffer, const GLfloat *vertices, const GLsizeiptr size);
void runaDeleteBuffer(gl_vertex_buffer_t *vertex_buffer);
void runaBindBuffer(gl_vertex_buffer_t *vertex_buffer);
void runaUnbindBuffer();

#ifdef __cplusplus
}
#endif
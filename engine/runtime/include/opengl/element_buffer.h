#pragma once

#include <glad/glad.h>

typedef struct {
    GLuint id;
    GLsizeiptr size;
}gl_element_buffer_t;

void runa_glGenElementBuffer(gl_element_buffer_t *element_buffer, const GLuint *indices, const GLsizeiptr size);
void runa_glDeleteElementBuffer(gl_element_buffer_t *element_buffer);
void runa_glBindElementBuffer(gl_element_buffer_t *element_buffer);
void runa_glUnbindElementBuffer();
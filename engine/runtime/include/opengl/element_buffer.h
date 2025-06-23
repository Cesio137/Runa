#pragma once

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
    GLsizeiptr size;
} gl_element_buffer_t;

void gl_GenElementBuffer(gl_element_buffer_t *element_buffer, const GLuint *indices, const GLsizeiptr size);
void gl_DeleteElementBuffer(gl_element_buffer_t *element_buffer);
void gl_BindElementBuffer(gl_element_buffer_t *element_buffer);
void gl_UnbindElementBuffer();

#ifdef __cplusplus
}
#endif
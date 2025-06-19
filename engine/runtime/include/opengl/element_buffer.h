#pragma once

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLuint id;
    GLsizeiptr size;
} gl_element_buffer_t;

void runaGenElementBuffer(gl_element_buffer_t *element_buffer, const GLuint *indices, const GLsizeiptr size);
void runaDeleteElementBuffer(gl_element_buffer_t *element_buffer);
void runaBindElementBuffer(gl_element_buffer_t *element_buffer);
void runaUnbindElementBuffer();

#ifdef __cplusplus
}
#endif
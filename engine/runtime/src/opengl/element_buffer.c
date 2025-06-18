#include "opengl/element_buffer.h"
#include "opengl/element_count.h"

void runa_glGenElementBuffer(gl_element_buffer_t *element_buffer, const GLuint *indices, const GLsizeiptr size) {
    glGenBuffers(1, &element_buffer->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,element_buffer->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    element_buffer->size = size;
    glElementCount += size / sizeof(GLuint);
}

void runa_glDeleteElementBuffer(gl_element_buffer_t *element_buffer) {
    if (glElementCount - element_buffer->size < 0) {
        glElementCount = 0;
    }
    else {
        glElementCount -= element_buffer->size;
    }
    glDeleteBuffers(1, &element_buffer->id);
}

void runa_glBindElementBuffer(gl_element_buffer_t *element_buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer->id);
}

void runa_glUnbindElementBuffer() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
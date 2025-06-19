#include "opengl/element_buffer.h"
#include "opengl/element_count.h"

void runaGenElementBuffer(gl_element_buffer_t *element_buffer, const GLuint *indices, const GLsizeiptr size) {
    element_buffer->id = 0;
    element_buffer->size = 0;
    glGenBuffers(1, &element_buffer->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    element_buffer->size = size;
    GL_ELEMENT_COUNT += size / sizeof(GLuint);
}

void runaDeleteElementBuffer(gl_element_buffer_t *element_buffer) {
    if (GL_ELEMENT_COUNT - element_buffer->size < 0) {
        GL_ELEMENT_COUNT = 0;
    } else {
        GL_ELEMENT_COUNT -= element_buffer->size;
    }
    glDeleteBuffers(1, &element_buffer->id);
}

void runaBindElementBuffer(gl_element_buffer_t *element_buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer->id);
}

void runaUnbindElementBuffer() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

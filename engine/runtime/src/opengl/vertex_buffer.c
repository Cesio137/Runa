#include "opengl/vertex_buffer.h"

void runaGenBuffer(gl_vertex_buffer_t *vertex_buffer, const GLfloat *vertices, const GLsizeiptr size) {
    glGenBuffers(1, &vertex_buffer->id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void runaDeleteBuffer(gl_vertex_buffer_t *vertex_buffer) {
    glDeleteBuffers(1, &vertex_buffer->id);
}

void runaBindBuffer(gl_vertex_buffer_t *vertex_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
}

void runaUnbindBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

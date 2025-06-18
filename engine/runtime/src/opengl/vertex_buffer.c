#include "opengl/vertex_buffer.h"

void runa_glGenBuffer(gl_vertex_buffer_t *vertex_buffer, const GLfloat *vertices, const GLsizeiptr size) {
    glGenBuffers(1, &vertex_buffer->id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void runa_glDeleteBuffer(gl_vertex_buffer_t *vertex_buffer) {
    glDeleteBuffers(1, &vertex_buffer->id);
}

void runa_glBindBuffer(gl_vertex_buffer_t *vertex_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
}

void runa_glUnbindBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

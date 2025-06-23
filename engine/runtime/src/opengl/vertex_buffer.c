#include "opengl/vertex_buffer.h"

void gl_GenVertexBuffer(gl_vertex_buffer_t *vertex_buffer, const GLfloat *vertices, const GLsizeiptr size) {
    glGenBuffers(1, &vertex_buffer->id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void gl_DeleteVertexBuffer(gl_vertex_buffer_t *vertex_buffer) {
    glDeleteBuffers(1, &vertex_buffer->id);
}

void gl_BindVertexBuffer(gl_vertex_buffer_t *vertex_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
}

void gl_UnbindVertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

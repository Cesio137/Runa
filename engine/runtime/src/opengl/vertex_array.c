#include "opengl/vertex_array.h"

void runa_glGenVertexArray(gl_vertex_array_t *vertex_array, const GLfloat *vertices, const GLsizeiptr size) {
    glGenVertexArrays(1, &vertex_array->id);
}

void runa_glDeleteVertexArray(gl_vertex_array_t *vertex_array) {
    glDeleteVertexArrays(1, &vertex_array->id);
}

void runa_glBindBuffer(gl_vertex_array_t *vertex_array) {
    glBindVertexArray(vertex_array->id);
}

void runa_glUnbindBuffer() {
    glBindVertexArray(0);
}

void runa_EnableVertexAttribArray(gl_vertex_array_t *vertex_array, gl_vertex_buffer_t *vertex_buffer, const GLuint layout, GLuint num, GLenum type, GLsizeiptr stride, void *offset) {
    runa_glBindBuffer(vertex_buffer);
    glVertexAttribPointer(layout, num, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    runa_glUnbindBuffer();
}

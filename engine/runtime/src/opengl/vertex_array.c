#include "opengl/vertex_array.h"

void gl_GenVertexArray(gl_vertex_array_t *vertex_array) {
    glGenVertexArrays(1, &vertex_array->id);
}

void gl_DeleteVertexArray(gl_vertex_array_t *vertex_array) {
    glDeleteVertexArrays(1, &vertex_array->id);
}

void gl_BindVertexArray(gl_vertex_array_t *vertex_array) {
    glBindVertexArray(vertex_array->id);
}

void gl_UnbindVertexArray() {
    glBindVertexArray(0);
}

void gl_EnableVertexAttribArray(gl_vertex_buffer_t *vertex_buffer, const GLuint layout, GLuint num, GLenum type,
                                 GLsizeiptr stride, void *offset) {
    gl_BindVertexBuffer(vertex_buffer);
    glVertexAttribPointer(layout, num, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    gl_UnbindVertexBuffer();
}

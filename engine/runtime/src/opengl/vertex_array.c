#include "opengl/vertex_array.h"

void runaGenVertexArray(gl_vertex_array_t *vertex_array) {
    glGenVertexArrays(1, &vertex_array->id);
}

void runaDeleteVertexArray(gl_vertex_array_t *vertex_array) {
    glDeleteVertexArrays(1, &vertex_array->id);
}

void runaBindVertexArray(gl_vertex_array_t *vertex_array) {
    glBindVertexArray(vertex_array->id);
}

void runaUnbindVertexArray() {
    glBindVertexArray(0);
}

void runaEnableVertexAttribArray(gl_vertex_buffer_t *vertex_buffer, const GLuint layout, GLuint num, GLenum type,
                                 GLsizeiptr stride, void *offset) {
    runaBindBuffer(vertex_buffer);
    glVertexAttribPointer(layout, num, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    runaUnbindBuffer();
}

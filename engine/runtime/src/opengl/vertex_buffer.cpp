#include "opengl/vertex_buffer.h"

namespace runa::opengl {
    gl_vertex_buffer_c::gl_vertex_buffer_c(const GLfloat *vertices, const GLsizeiptr size) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    gl_vertex_buffer_c::~gl_vertex_buffer_c() {
        glDeleteBuffers(1, &id);
    }

    void gl_vertex_buffer_c::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void gl_vertex_buffer_c::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
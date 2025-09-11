#include "opengl/vertex_array.h"

namespace runa::opengl {
    gl_vertex_array_c::gl_vertex_array_c() {
        glGenVertexArrays(1, &id);
    }

    gl_vertex_array_c::~gl_vertex_array_c() {
        glDeleteVertexArrays(1, &id);
    }

    void gl_vertex_array_c::bind() const {
        glBindVertexArray(id);
    }

    void gl_vertex_array_c::unbind() const {
        glBindVertexArray(0);
    }

    void gl_vertex_array_c::enable_attrib(const gl_vertex_buffer_c &vertex_buffer, const GLuint layout, GLuint num, GLenum type, GLsizeiptr stride, void *offset) const {
        vertex_buffer.bind();
        glVertexAttribPointer(layout, num, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        vertex_buffer.unbind();
    }
}

#include "opengl/vertex_array.h"
#include "opengl/vertex_buffer.h"

namespace Runa::Opengl {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &BufferID);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &BufferID);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(BufferID);
    }

    void VertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::EnableVertexAttribArray(const VertexBuffer &vbo, const GLuint layout, GLuint num, GLenum type, GLsizeiptr stride, void* offset) const {
        vbo.Bind();
        glVertexAttribPointer(layout, num, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        vbo.Unbind();
    }
}

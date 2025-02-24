#include "opengl/vertex_buffer.h"


namespace Runa::Opengl {
    VertexBuffer::VertexBuffer(const GLfloat *vertices, const GLsizeiptr size) {
        glGenBuffers(1, &BufferID);
        glBindBuffer(GL_ARRAY_BUFFER, BufferID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &BufferID);
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, BufferID);
    }

    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

#include "opengl/element_buffer.h"
#include "opengl/element_count.h"

namespace Runa::Opengl {
    ElementBuffer::ElementBuffer(const GLuint *indices, const GLsizeiptr size): ElementSize(size) {
        glGenBuffers(1, &BufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
        Opengl::Elements::Count += size / sizeof(GLuint);
    }

    ElementBuffer::~ElementBuffer() {
        if (Opengl::Elements::Count - ElementSize < 0) {
            Opengl::Elements::Count = 0;
        }
        else {
            Opengl::Elements::Count -= ElementSize;
        }
        glDeleteBuffers(1, &BufferID);
    }

    void ElementBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
    }

    void ElementBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

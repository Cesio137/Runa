#pragma once

#include <glad/glad.h>

namespace Runa::Opengl {
    class VertexBuffer {
    public:
        VertexBuffer(const GLfloat *vertices, const GLsizeiptr size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        GLuint GetBufferID() const { return BufferID; }
    private:
        GLuint BufferID = 0;
    };
}

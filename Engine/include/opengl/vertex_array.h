#pragma once

#include <glad/glad.h>

namespace Runa::Opengl {
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;
        void EnableVertexAttribArray(const class VertexBuffer &vbo, const GLuint layout, GLuint num, GLenum type, GLsizeiptr stride, void* offset) const;

        GLuint GetBufferID() const { return BufferID; }

    private:
        GLuint BufferID = 0;
    };
}

#pragma once

#include <glad/glad.h>

namespace Runa::Opengl {
    class ElementBuffer {
    public:
        ElementBuffer(const GLuint *indices, const GLsizeiptr size);
        ~ElementBuffer();

        void Bind() const;
        void Unbind() const;
        GLuint GetBufferID() const { return BufferID; }

    private:
        GLuint BufferID = 0;
        const GLsizeiptr ElementSize = 0;
    };
}

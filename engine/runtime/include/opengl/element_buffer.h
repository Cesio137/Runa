#pragma once

#include <glad/glad.h>

namespace runa::opengl {
    class gl_element_buffer_c {
    public:
        gl_element_buffer_c(const GLuint *indices, const GLsizeiptr size);
        ~gl_element_buffer_c();

        void bind() const;
        void unbind() const;
    private:
        GLuint id;
        GLsizeiptr size;
    };
}
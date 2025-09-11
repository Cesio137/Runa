#pragma once

#include <glad/glad.h>

namespace runa::opengl {
    class gl_vertex_buffer_c {
    public:
        gl_vertex_buffer_c(const GLfloat *vertices, const GLsizeiptr size);
        ~gl_vertex_buffer_c();

        void bind() const;
        void unbind() const;
    private:
        GLuint id;
    };
}
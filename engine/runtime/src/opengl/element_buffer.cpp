#include "opengl/element_buffer.h"
#include "opengl/element_count.h"

namespace runa::opengl {
    gl_element_buffer_c::gl_element_buffer_c(const GLuint *indices, const GLsizeiptr size) {
        id = 0;
        this->size = 0;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
        this->size = size;
        GL_ELEMENT_COUNT += size / sizeof(GLuint);
    }

    gl_element_buffer_c::~gl_element_buffer_c() {
        if (GL_ELEMENT_COUNT - size < 0) {
            GL_ELEMENT_COUNT = 0;
        } else {
            GL_ELEMENT_COUNT -= size;
        }
        glDeleteBuffers(1, &id);
    }

    void gl_element_buffer_c::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void gl_element_buffer_c::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

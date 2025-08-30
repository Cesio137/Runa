#pragma once

#include <string>
#include <glad/glad.h>

namespace runa::opengl {
    class gl_shader_c {
    public:
        gl_shader_c(const std::string &vertexfile, const std::string &fragmentfile);
        ~gl_shader_c();

        void use() const;
        void set_uniform_location(const char *uniform, const GLuint unit) const;
        GLuint get_id() const { return id; }
    private:
        GLuint id;
    };
}

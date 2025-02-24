#pragma once

#include <glad/glad.h>
#include <string>

namespace Runa::Shaders {
    class GLShader {
    public:
        GLShader(const std::string &vertexfile, const std::string &fragmentfile);
        ~GLShader();

        void UseProgram() const;

        GLuint GetProgramID() const { return ProgramID; }

    private:
        GLuint ProgramID = 0;
    };
}

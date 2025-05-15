#pragma once

#include <glad/glad.h>
#include <EASTL/string.h>

namespace Runa::Shaders {
    class GLShader {
    public:
        GLShader(const char *vertexfile, const char *fragmentfile);
        ~GLShader();

        void UseProgram() const;

        GLuint GetProgramID() const { return ProgramID; }

    private:
        GLuint ProgramID = 0;
    };
}

#include "shaders/glshaders.h"
#include "core/system/file.h"

using namespace Runa::System;

namespace Runa::Shaders {
    GLShader::GLShader(const std::string &vertexfile, const std::string &fragmentfile) {
        // Read vertexFile and fragmentFile and store the strings
        const std::string vertexCode = LoadFileToString(vertexfile);
        const std::string fragmentCode = LoadFileToString(fragmentfile);

        // Convert the shader source strings into character arrays
        const char *vertex_source = vertexCode.c_str();
        const char *fragment_source = fragmentCode.c_str();

        // Create Vertex Shader Object and get its reference
        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        // Attach Vertex Shader source to the Vertex Shader Object
        glShaderSource(vertex_shader, 1, &vertex_source, NULL);
        // Compile the Vertex Shader into machine code
        glCompileShader(vertex_shader);

        // Create Fragment Shader Object and get its reference
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        // Attach Fragment Shader source to the Fragment Shader Object
        glShaderSource(fragment_shader, 1, &fragment_source, NULL);
        // Compile the Vertex Shader into machine code
        glCompileShader(fragment_shader);

        // Create Shader Program Object and get its reference
        ProgramID = glCreateProgram();
        // Attach the Vertex and Fragment Shaders to the Shader Program
        glAttachShader(ProgramID, vertex_shader);
        glAttachShader(ProgramID, fragment_shader);
        // Wrap-up/Link all the shaders together into the Shader Program
        glLinkProgram(ProgramID);

        // Delete the now useless Vertex and Fragment Shader objects
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    GLShader::~GLShader() {
        glDeleteProgram(ProgramID);
    }

    void GLShader::UseProgram() const {
        glUseProgram(ProgramID);
    }
}

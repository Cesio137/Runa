#include "shaders/glshader.h"
#include "utils/system/file.h"
#include <SDL3/SDL.h>


int gl_CreateShaderProgram(gl_shader_t *gl_shader, const char *vertexfile, const char *fragmentfile) {
    gl_shader->id = 0;

    // Convert the shader source strings into character arrays
    cstr vertex_source = runaLoadTextFile(vertexfile);
    cstr fragment_source = runaLoadTextFile(fragmentfile);

    // Create Vertex Shader Object and get its reference
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    const char *src = cstr_str(&vertex_source);
    glShaderSource(vertex_shader, 1, &src, NULL);
    cstr_drop(&vertex_source);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertex_shader);

    // Create Fragment Shader Object and get its reference
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    src = cstr_str(&fragment_source);
    glShaderSource(fragment_shader, 1, &src, NULL);
    cstr_drop(&fragment_source);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragment_shader);

    // Create Shader Program Object and get its reference
    gl_shader->id = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(gl_shader->id, vertex_shader);
    glAttachShader(gl_shader->id, fragment_shader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(gl_shader->id);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return 0;
}

void gl_DeleteShaderProgram(gl_shader_t *gl_shader) {
    glDeleteProgram(gl_shader->id);
}

void gl_UseShaderProgram(gl_shader_t *gl_shader) {
    glUseProgram(gl_shader->id);
}

void gl_SetUniformLocation(gl_shader_t *shader, const char *uniform, const GLuint unit) {
    // Gets the location of the uniform
    GLuint texuni = glGetUniformLocation(shader->id, uniform);
    // Shader needs to be activated before changing the value of a uniform
    gl_UseShaderProgram(shader);
    // Sets the value of the uniform
    glUniform1i(texuni, unit);
}

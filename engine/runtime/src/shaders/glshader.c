#include "shaders/glshader.h"
#include "core/system/file.h"
#include <SDL3/SDL.h>


int runaCreateShaderProgram(gl_shader_t *gl_shader, const char *vertexfile, const char *fragmentfile) {
    gl_shader->id = 0;

    // Convert the shader source strings into character arrays
    char *vertex_source = runaLoadFile(vertexfile);
    char *fragment_source = runaLoadFile(fragmentfile);

    // Create Vertex Shader Object and get its reference
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    SDL_free(vertex_source);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertex_shader);

    // Create Fragment Shader Object and get its reference
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    SDL_free(vertex_source);
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

void runaDeleteShaderProgram(gl_shader_t *gl_shader) {
    glUseProgram(gl_shader->id);
}

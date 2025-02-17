#include <array>
#include <iostream>
#include "render/render.h"
#include "glm/vec4.hpp"

using namespace Runa;

// Vertex Shader source code
const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main(int argc, char *argv[])
{
    RenderInterface rhi(ESDL_Driver::CORE_460);

    GLuint vertex_shader;
    GLuint fragment_shader;
	GLuint shader_program;
    GLfloat vertices[] =
	{
		-0.25f, -0.25f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.25f, -0.25f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};
    GLuint VAO, VBO;

    rhi.OnPreInitialize = [&](ImGuiIO &io) {

    };
    rhi.OnReady = [&]() {
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertex_shader);

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	    glShaderSource(fragment_shader, 1, &fragmentShaderSource, NULL);
	    glCompileShader(fragment_shader);

        shader_program = glCreateProgram();
        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    };
    rhi.OnEventHandle = [&](SDL_Event event) {
        
    };
    rhi.OnRenderImgui = [&](ImGuiIO &io) {
        ImGui::Begin("teste");
        ImGui::Text("teste");
        ImGui::End();
    };
    rhi.OnRender = [&](float delta) {
        glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
    };
    int code = rhi.Exec();
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader_program);
    if (code)
    {
        std::cerr << SDL_GetError() << std::endl;
        return code;
    }

    return 0;
}


#include <array>
#include <iostream>
#include <cmath>
#include <filesystem>
#ifndef _WIN64
#include <memory>
#endif
#include "core/system/path.h"
#include "render/glrender.h"
#include "opengl/element_buffer.h"
#include "opengl/vertex_array.h"
#include "opengl/vertex_buffer.h"
#include "opengl/element_count.h"
#include "opengl/texture.h"
#include "glm/vec4.hpp"
#include "core/system/file.h"
#include "shaders/glshaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace Runa;

int main() {
    stbi_set_flip_vertically_on_load(true);
    Render::OpenglInterface rhi(Render::CORE_460);
    std::unique_ptr<Shaders::GLShader> shader;
    GLfloat vertices[] =
    {  /*   COORDENATES   */    /*    COLOR    */
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,       0.0f, 0.0f,// Lower left corner
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,       0.0f, 1.0f,// Upper left corner
         0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,       1.0f, 1.0f,// Upper right corner
         0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,       1.0f, 0.0f,// Lower right corner
    };
    GLuint indices[] = {
        0, 2, 1, // Lower triangle
        0, 3, 2, // Upper triangle
    };
    std::unique_ptr<Opengl::ElementBuffer> EBO;
    std::unique_ptr<Opengl::VertexArray> VAO;
    std::unique_ptr<Opengl::VertexBuffer> VBO;
    std::unique_ptr<Opengl::Texture> Tex;

    GLuint uniID;

    rhi.OnPreInitialize = [&](ImGuiIO &io) {
    };
    rhi.OnReady = [&]() {
        rhi.SetVSync(1);
        shader = std::make_unique<Shaders::GLShader>(System::CurrentDir() + "/resources/shaders/default.vert", System::CurrentDir() + "/resources/shaders/default.frag");
        VAO = std::make_unique<Opengl::VertexArray>();
        VAO->Bind();
        VBO = std::make_unique<Opengl::VertexBuffer>(vertices, sizeof(vertices));
        EBO = std::make_unique<Opengl::ElementBuffer>(indices, sizeof(indices));
        VAO->EnableVertexAttribArray(*VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void *) 0);
        VAO->EnableVertexAttribArray(*VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        VAO->EnableVertexAttribArray(*VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        VAO->Unbind();
        VBO->Unbind();
        EBO->Unbind(); 
        
        uniID = glGetUniformLocation(shader->GetProgramID(), "scale");
        std::string workdir = System::CurrentDir() + "/resources/textures/albedo.jpg";
        workdir = System::NativeSeparator(workdir);
        Tex = std::make_unique<Opengl::Texture>(workdir, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        Tex->SetUniformLocation(*shader, "tex0", 0);
    };
    rhi.OnEventHandle = [&](SDL_Event event) {
    };
    rhi.OnRenderImgui = [&](ImGuiIO &io) {
        ImGui::Begin("teste");
        ImGui::Text("teste");
        ImGui::End();
    };
    rhi.OnRender = [&](float delta) {
        shader->UseProgram();
        glUniform1f(uniID, 0.5f);
        Tex->Bind();
        VAO->Bind();
        glDrawElements(GL_TRIANGLES, Opengl::Elements::Count, GL_UNSIGNED_INT, 0);
    };
    int code = rhi.Exec();
    if (code) {
        std::cerr << SDL_GetError() << std::endl;
        return code;
    }

    return 0;
}

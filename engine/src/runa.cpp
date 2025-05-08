#include "core/ea/eamalloc.h"
#include <iostream>
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
#include <EASTL/string.h>
#include <EASTL/unique_ptr.h>

using namespace Runa;

int main() {
    stbi_set_flip_vertically_on_load(true);
    Render::OpenglInterface rhi(Render::CORE_460);
    eastl::unique_ptr<Shaders::GLShader> shader;
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
    eastl::unique_ptr<Opengl::ElementBuffer> EBO;
    eastl::unique_ptr<Opengl::VertexArray> VAO;
    eastl::unique_ptr<Opengl::VertexBuffer> VBO;
    eastl::unique_ptr<Opengl::Texture> Tex;

    GLuint uniID;

    rhi.OnPreInitialize = [&](ImGuiIO &io) {
    };
    rhi.OnReady = [&]() {
        rhi.SetVSync(1);
        const eastl::string currentDir = System::CurrentDir();
        const eastl::string vert_shader = currentDir + "/resources/shaders/default.vert";
        const eastl::string frag_shader = currentDir + "/resources/shaders/default.frag";
        shader = eastl::make_unique<Shaders::GLShader>(vert_shader.c_str(), frag_shader.c_str());
        VAO = eastl::make_unique<Opengl::VertexArray>();
        VAO->Bind();
        VBO = eastl::make_unique<Opengl::VertexBuffer>(vertices, sizeof(vertices));
        EBO = eastl::make_unique<Opengl::ElementBuffer>(indices, sizeof(indices));
        VAO->EnableVertexAttribArray(*VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void *) 0);
        VAO->EnableVertexAttribArray(*VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        VAO->EnableVertexAttribArray(*VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        VAO->Unbind();
        VBO->Unbind();
        EBO->Unbind(); 
        
        uniID = glGetUniformLocation(shader->GetProgramID(), "scale");
        eastl::string workdir = currentDir + "/resources/textures/albedo.jpg";
        workdir = System::NativeSeparator(workdir.c_str());
        Tex = eastl::make_unique<Opengl::Texture>(workdir, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
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
        SDL_Log("%s", SDL_GetError());
        return code;
    }

    return 0;
}

//#define STC_CSTR_CORE
#include <iostream>
#include "opengl/camera.h"
#include <render/sdl_glrender.h>
#include <opengl/element_buffer.h>
#include <opengl/vertex_array.h>
#include <opengl/vertex_buffer.h>
#include <opengl/texture.h>
#include <shaders/glshader.h>
#include <utils/system/path.h>
#include <utils/system/file.h>
#include <opengl/element_count.h>

using namespace runa::render;
using namespace runa::opengl;

int main(int argc, char** argv) {
    sdl_glrender_c rhi = sdl_glrender_c();

    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
        0.5f, 0.0f, -0.5f,      0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        0.5f, 0.0f,  0.5f,      0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
        0.0f, 0.8f,  0.0f,      0.92f, 0.86f, 0.76f,	2.5f, 5.0f
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    std::unique_ptr<shader_c> shader;
    std::unique_ptr<element_buffer_c> EBO;
    std::unique_ptr<vertex_array_c> VAO;
    std::unique_ptr<vertex_buffer_c> VBO;
    std::unique_ptr<texture_c> tex;

    GLuint uniID;
    int viewport_width = 1024;
    int viewport_height = 576;

    camera_c camera = camera_c(viewport_width, viewport_height, glm::vec3(0.0f, 0.0f, 2.0f));

    rhi.on_ready = [&]() {
        rhi.set_vsync(1);
        const std::string currentDir = runa::utils::path::current_dir();
        const std::string vert_shader = currentDir + "resources/shaders/default.vert";
        const std::string frag_shader = currentDir + "resources/shaders/default.frag";
        const std::string src = runa::utils::file::load_text_file(frag_shader);
        std::cout << "Shader: " << src << std::endl;
        shader = std::make_unique<shader_c>(vert_shader, frag_shader);
        VAO = std::make_unique<vertex_array_c>();
        VAO->bind();
        VBO = std::make_unique<vertex_buffer_c>(vertices, sizeof(vertices));
        EBO = std::make_unique<element_buffer_c>(indices, sizeof(indices));
        VAO->enable_attrib(*VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
        VAO->enable_attrib(*VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        VAO->enable_attrib(*VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        VAO->unbind();

        VAO->unbind();
        VBO->unbind();
        EBO->unbind();

        uniID = glGetUniformLocation(shader->get_id(), "scale");
        std::string albedodir = currentDir + "resources/textures/brick.png";
        tex = std::make_unique<texture_c>(albedodir, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        std::cout << tex->is_valid() << std::endl;
        shader->set_uniform_location("tex0", 0);
    };
    rhi.on_eventhandle = [&](SDL_Event event) {
        if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            SDL_GetWindowSizeInPixels(rhi.get_backend()->window_ptr, &viewport_width, &viewport_height);
        }
        camera.inputs(event);
    };
    rhi.on_imguirender = [&](ImGuiIO &io) {
        ImGui::Begin("teste");
        ImGui::Text("teste");
        ImGui::End();
    };
    rhi.on_render = [&](float delta) {
        shader->use();

        camera.tick(delta);
        camera.matrix(60.0f, 0.1f, 100.0f, *shader, "camMatrix");

        glUniform1f(uniID, 0.5f);
        tex->bind();
        VAO->bind();
        glDrawElements(GL_TRIANGLES, GL_ELEMENT_COUNT, GL_UNSIGNED_INT, 0);
    };

    int code = rhi.run(GL_DRIVER_OPENGLCORE);

    if (code != 0) {
        SDL_Log("%s", SDL_GetError());
        return code;
    }

    return 0;
}

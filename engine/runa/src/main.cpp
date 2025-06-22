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

    gl_shader_t shader;
    gl_element_buffer_t EBO;
    gl_vertex_array_t VAO;
    gl_vertex_buffer_t VBO;
    gl_texture_t tex;

    GLuint uniID;
    int viewport_width = 1024;
    int viewport_height = 576;

    camera_c camera = camera_c(viewport_width, viewport_height, glm::vec3(0.0f, 0.0f, 2.0f));

    rhi.on_ready = [&]() {
        rhi.set_vsync(1);
        const std::string currentDir = runaCurrentDir();
        const std::string vert_shader = currentDir + "resources/shaders/default.vert";
        const std::string frag_shader = currentDir + "resources/shaders/default.frag";
        runaCreateShaderProgram(&shader, vert_shader.c_str(), frag_shader.c_str());
        runaGenVertexArray(&VAO);
        runaBindVertexArray(&VAO);
        runaGenBuffer(&VBO, vertices, sizeof(vertices));
        runaGenElementBuffer(&EBO, indices, sizeof(indices));
        runaEnableVertexAttribArray(&VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
        runaEnableVertexAttribArray(&VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        runaEnableVertexAttribArray(&VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        runaUnbindVertexArray();
        runaUnbindBuffer();
        runaUnbindElementBuffer();

        uniID = glGetUniformLocation(shader.id, "scale");
        std::string albedodir = currentDir + "resources/textures/brick.png";
        cstr native_path = runaNativeSeparator(albedodir.c_str());
        albedodir = cstr_str(&native_path);
        cstr_drop(&native_path);
        runaGenTexture(&tex, albedodir.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        runaSetUniformLocation(&shader, "tex0", 0);
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
        runaUseShaderProgram(&shader);

        camera.tick(delta);
        camera.matrix(60.0f, 0.1f, 100.0f, &shader, "camMatrix");

        glUniform1f(uniID, 0.5f);
        runaBindTexture(&tex);
        runaBindVertexArray(&VAO);
        glDrawElements(GL_TRIANGLES, GL_ELEMENT_COUNT, GL_UNSIGNED_INT, 0);
    };

    int code = rhi.run(sdl_gldriver_t::GL_DRIVER_OPENGLCORE);

    runaDeleteElementBuffer(&EBO);
    runaDeleteBuffer(&VBO);
    runaDeleteVertexArray(&VAO);
    runaDeleteShaderProgram(&shader);
    runaDeleteTexture(&tex);

    if (code != 0) {
        SDL_Log("%s", SDL_GetError());
        return code;
    }

    return 0;
}

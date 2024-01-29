#pragma once

#include <glad/gl.h>
#ifdef __linux__
#include <glad/glx.h>
#endif
#include <SDL.h>
#include <imgui.h>

#include <string>

namespace Nanometro
{
    class Opengl
    {
    public:
        explicit Opengl();
        ~Opengl();
        void Opengl_ImGuiInit();
        void Opengl_ImGuiDestroy();

        SDL_Window* GetWindow();
        SDL_GLContext GetContext();
        std::pair<uint8_t, uint8_t> GetOpenglVersion();
        std::string GetGlslVersion();

        /* OpenGL log */
        int GetErrorCode();
        std::string GetErrorLog();

    private:

        /* OpenGL Window */
        int WindowShouldClose = 0;
        SDL_Window* Window;
        SDL_GLContext Context;

        /* OpenGL log */
        std::pair<uint8_t, uint8_t> Version;
        std::string error_log;
        int error_code = 0;

        /* Imgui */
        std::string glsl_Version;
    };
}

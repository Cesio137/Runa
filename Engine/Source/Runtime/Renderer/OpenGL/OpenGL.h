#pragma once

#include <string>

#include <glad/gl.h>
#ifdef __linux__
#include <glad/glx.h>
#endif

#include <SDL.h>
#include <SDL_syswm.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

namespace Nanometro
{
    class OpenGL
    {
    public:
        explicit OpenGL();
        ~OpenGL();
        void SDL2_ImGui_Init();
        void SDL2_Destroy_OpenGL();

        SDL_GLContext GetContext();
        SDL_Window* GetWindow();

        /* OpenGL log */
        int GetErrorCode() const;
        std::string GetErrorLog() const;

    private:

        /* OpenGL Window */
        bool WindowShouldClose = false;
        SDL_GLContext Context = nullptr;
        SDL_Window* Window = nullptr;

        /* OpenGL log */
        std::pair<uint8_t, uint8_t> Version;
        std::string error_log;
        int error_code = 0;

        /* Imgui */
        std::string glsl_Version;
    };
}

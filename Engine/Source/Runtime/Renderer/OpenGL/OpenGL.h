#pragma once

/*
#   Created by Nathan Miguel
*/

#ifndef NANOMETRO_OPENGL_H
#define NANOMETRO_OPENGL_H

#include <string>

#include <glad/gl.h>
#ifdef HOST_SYSTEM_LINUX
#include <glad/glx.h>
#endif

#include <SDL.h>
#include <SDL_syswm.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <RenderingConfig.h>
#include <Config.h>


using namespace std;

namespace OpenGL
{
    class SDL
    {
        //friend class RenderHardwareInterface;

    public:
        explicit SDL();
        ~SDL();
        void SDL2_ImGui_Init();
        void SDL2_Destroy_OpenGL();
        int GetErrorCode(string &log);
        static SDL_Window* GetWindow();

    private:

        /* OpenGL Window */
        bool WindowShouldClose = false;
        pair<uint8_t, uint8_t> OpenGL_Version;
        SDL_GLContext Context = nullptr;
        inline static SDL_Window* Window = nullptr;

        /* Imgui */
        string glsl_Version;

        /* error */
        string error_log;
        int error_code = 0;
    };

    class GLFW
    {
        //friend class RenderHardwareInterface;

    public:
        explicit GLFW();
        ~GLFW();
        void GLFW_ImGui_Init();
        void GLFW_Destroy_OpenGL();
        int GetErrorCode(string &log);
        static GLFWwindow* GetWindow();

    private:

        /* OpenGL Window */
        bool WindowShouldClose = false;
        pair<uint8_t, uint8_t> OpenGL_Version;
        inline static GLFWwindow* Window = nullptr;

        /* Imgui */
        string glsl_Version;

        /* error */
        string error_log;
        int error_code = 0;
    };
}
#endif //NANOMETRO_OPENGL_H

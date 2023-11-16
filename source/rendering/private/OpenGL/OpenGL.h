#pragma once

/*
#   Created by Nathan Miguel
*/

#ifndef NANOMETRO_OPENGL_H
#define NANOMETRO_OPENGL_H

#include <string>
#include <glad/glad.h>
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <RenderingConfig.h>
#include <Config.h>


using namespace std;

class SDL_OpenGL
{
    friend class RenderHardwareInterface;

private:
    explicit SDL_OpenGL();
    ~SDL_OpenGL();
    void SDL2_ImGui_Init();
    void SDL2_Destroy_OpenGL();
    int GetErrorCode(string &log);

    static SDL_Window* GetWindow();

    /* OpenGL Window */
    bool WindowShouldClose = false;
    pair<uint8_t, uint8_t> OpenGL_Version;
    SDL_Renderer* Renderer = nullptr;
    SDL_GLContext Context = nullptr;
    inline static SDL_Window* Window = nullptr;

    /* Imgui */
    string glsl_Version;

    /* error */
    string error_log;
    int error_code = 0;
};

#endif //NANOMETRO_OPENGL_H

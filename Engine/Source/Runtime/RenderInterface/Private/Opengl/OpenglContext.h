#pragma once

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "Opengl/Opengl.h"
#include "RenderSettings.h"
#include <glad/gl.h>
#ifdef __linux__
#include <glad/glx.h>
#endif
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include <memory>

namespace Nanometro{

    struct opengl_error {
        int code = 0;
        std::string log;
    };

    static opengl_error gl_error;

    inline void DestroyOpengl(Opengl &opengl)
    {
        if (opengl.Context)
            SDL_GL_DeleteContext(opengl.Context);
        if (opengl.Window)
            SDL_DestroyWindow(opengl.Window);
        opengl.Version.first = 0;
        opengl.Version.second = 0;
        memset(opengl.glsl_Version, 0, sizeof(opengl.glsl_Version));
        SDL_Quit();
    }

    inline Opengl ConstructOpengl(uint32_t flags)
    {
        Opengl opengl;

        gl_error.code = 0;
        gl_error.log = "";

        /* Init SDL Video */
        if (!SDL_WasInit(SDL_INIT_VIDEO))
        {
            if (SDL_InitSubSystem(SDL_INIT_VIDEO))
            {
                gl_error.code = SDL_INIT_VIDEO;
                gl_error.log = "SDL Video Subsystem could not be initialized: ";
                gl_error.log.append(SDL_GetError());
                return opengl;
            }
        }

        // Configure oepngl attribute
        if (flags == OPENGL_INIT_460)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
            opengl.Version.first = 4;
            opengl.Version.second = 6;
        }
        else if (flags == OPENGL_INIT_330)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            opengl.Version.first = 3;
            opengl.Version.second = 3;
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Create a SDL window
        opengl.Window = SDL_CreateWindow(ENGINE_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!opengl.Window)
        {
            gl_error.code = -1;
            if (flags == OPENGL_INIT_460)
                gl_error.log = "SDL could not create window using opengl 460: ";
            else if (flags == OPENGL_INIT_330)
                gl_error.log = "SDL could not create window using opengl 330: ";
            gl_error.log.append(SDL_GetError());
            DestroyOpengl(opengl);
            return opengl;
        }
        // Make the window's context current
        opengl.Context = SDL_GL_CreateContext(opengl.Window);
        if (!opengl.Context)
        {
            gl_error.code = -2;
            gl_error.log = "SDL could not create context: ";
            gl_error.log.append(SDL_GetError());
            DestroyOpengl(opengl);
            return opengl;
        }
        if (!gladLoadGL( reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress) ))
        {
            gl_error.code = -3;
            gl_error.log = "GLAD could not be loaded.";
            DestroyOpengl(opengl);
            return opengl;
        }
        std::string glsl = "#version " + std::to_string(opengl.Version.first) + std::to_string(opengl.Version.second) + "0";
        strcpy_s(opengl.glsl_Version, sizeof(opengl.glsl_Version), glsl.c_str());

        return opengl;
    }

    inline opengl_error Opengl_GetError()
    {
        return gl_error;
    }

    inline void Opengl_ImGuiInit(Opengl &opengl)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        ImGui_ImplSDL2_InitForOpenGL(opengl.Window, opengl.Context);
        ImGui_ImplOpenGL3_Init(opengl.glsl_Version);
    }

    inline void Opengl_ImGuiDestroy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

}

#endif //OPENGLCONTEXT_H
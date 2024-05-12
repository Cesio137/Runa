#ifndef SDL_OPENGLCONTEXT_H
#define SDL_OPENGLCONTEXT_H

#include "Opengl/SDL_Opengl.h"
#include <Config.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <memory>

namespace Nanometro{

    struct opengl_error {
        int code = 0;
        std::string log;
    };

    static opengl_error gl_error;

    inline void DestroyOpengl(SDL_Opengl &opengl)
    {        
        if (opengl.renderer_ptr)
            SDL_DestroyRenderer(opengl.renderer_ptr);
        if (opengl.window_ptr)
            SDL_DestroyWindow(opengl.window_ptr);
        opengl.version.first = 0;
        opengl.version.second = 0;
        SDL_Quit();
    }

    inline SDL_Opengl ConstructOpengl(uint32_t flags)
    {
        SDL_Opengl opengl;

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
            opengl.version.first = 4;
            opengl.version.second = 6;
        }
        else if (flags == OPENGL_INIT_330)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            opengl.version.first = 3;
            opengl.version.second = 3;
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Create a SDL window
        opengl.window_ptr = SDL_CreateWindow(ENGINE_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!opengl.window_ptr)
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

        opengl.renderer_ptr = SDL_CreateRenderer(opengl.window_ptr, -1, 0);
        if (!opengl.renderer_ptr)
        {
            gl_error.code = -2;
            gl_error.log = "SDL could not create renderer: ";
            gl_error.log.append(SDL_GetError());
            DestroyOpengl(opengl);
            return opengl;
        }

        return opengl;
    }

    inline opengl_error Opengl_GetError()
    {
        return gl_error;
    }

    inline void SDL_ImGuiInit(SDL_Opengl &opengl)
    {
        if (!opengl.window_ptr || !opengl.renderer_ptr)
            return;
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplSDL2_InitForSDLRenderer(opengl.window_ptr, opengl.renderer_ptr);
        ImGui_ImplSDLRenderer2_Init(opengl.renderer_ptr);
    }

    inline void SDL_ImGuiDestroy()
    {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

}

#endif //SDL_OPENGLCONTEXT_H
#pragma once

#include "Opengl/SDL_Opengl.h"
#include <Config.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <memory>

namespace Nanometro
{
    inline void SDL_ImGuiInit(FSDL_Opengl &opengl)
    {
        if (!opengl.window_ptr || !opengl.renderer_ptr)
            return;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
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
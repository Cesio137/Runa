#pragma once

#include "Opengl/SDL_Opengl.h"
#include <Config.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
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
        ImGui_ImplSDL3_InitForSDLRenderer(opengl.window_ptr, opengl.renderer_ptr);
        ImGui_ImplSDLRenderer3_Init(opengl.renderer_ptr);
    }

    inline void SDL_ImGuiDestroy()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
}
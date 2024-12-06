#pragma once

#include "../../Public/Backend/SDL_Backend.h"
#include <Config.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <memory>

namespace Runa
{
    inline void SDL_ImGuiInit(FSDL_Backend &backend)
    {
        if (!backend.window_ptr || !backend.renderer_ptr)
            return;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        ImGui_ImplSDL3_InitForSDLRenderer(backend.window_ptr, backend.renderer_ptr);
        ImGui_ImplSDLRenderer3_Init(backend.renderer_ptr);
    }

    inline void SDL_ImGuiDestroy()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
}
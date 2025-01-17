#pragma once

#include "render/backend/sdl_imgui.h"

namespace Runa {
    void SDL_ImGuiInit(FSDL_Backend &backend) {
        if (!backend.window_ptr || !backend.renderer_ptr)
            return;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        ImGui_ImplSDL3_InitForSDLRenderer(backend.window_ptr, backend.renderer_ptr);
        ImGui_ImplSDLRenderer3_Init(backend.renderer_ptr);
    }

    void SDL_ImGuiDestroy() {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
}

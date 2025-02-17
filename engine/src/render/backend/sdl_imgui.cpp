#pragma once

#include "render/backend/sdl_imgui.h"

namespace Runa {
    void SDL_ImGuiInit(FSDL_Backend &backend) {
        if (!backend.window_ptr || !backend.gl_context)
            return;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        ImGui_ImplSDL3_InitForOpenGL(backend.window_ptr, backend.gl_context);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void SDL_ImGuiDestroy() {
        ImGui_ImplSDL3_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }
}

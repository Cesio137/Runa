#include "render/backend/sdl_imgui.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

namespace Runa::Render {
    void SDL_GL_ImGuiInit(FSDL_GL_Backend &backend) {
        if (!backend.window_ptr || !backend.gl_context)
            return;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui_ImplSDL3_InitForOpenGL(backend.window_ptr, backend.gl_context);
        ImGui_ImplOpenGL3_Init(backend.glsl_version);
    }

    void SDL_GL_ImGuiDestroy() {
        ImGui_ImplSDL3_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }
}

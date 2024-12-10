#include "RenderInterface.h"
#include "Backend/SDL_ImGui.h"
#include <SDL3/SDL_render.h>
#include <iostream>

namespace Runa {
    RenderInterface::RenderInterface(ESDL_Driver driver) { m_Driver = driver; }

    RenderInterface::~RenderInterface() {
        SDL_ImGuiDestroy();
        SDL_Quit();
    }

    int RenderInterface::Exec() {
        int code = InitDriver(m_Backend, m_Driver);
        if (code) return code;
        m_Renderer();
        return 0;
    }

    void RenderInterface::CloseApp() {
        m_WindowShouldClose = true;
    }

    bool RenderInterface::SetVSync(int vsync) {
        return SDL_SetRenderVSync(m_Backend.renderer_ptr, vsync);
    }

    bool RenderInterface::GetVSync(int &vsync) {
        return SDL_GetRenderVSync(m_Backend.renderer_ptr, &vsync);
    }

    void RenderInterface::SetFrameRateLimit(int fps) {
        if (fps <= 0) fps = 0;
        m_FrameRateLimit = fps;
    }

    int RenderInterface::GetFrameRateLimit() {
        return m_FrameRateLimit;
    }

    const FSDL_Backend *RenderInterface::GetBackend() {
        return &m_Backend;
    }

    void RenderInterface::m_Renderer() {
        SDL_ImGuiInit(m_Backend);
        PreInitialize(ImGui::GetIO());
        // Framerate limit
        int vsync = 0;
        uint64_t start = 0;
        uint64_t elapsed = 0;
        uint64_t frame_time = 0;
        // Ready
        Ready();
        // Main loop
        SDL_Event event;
        while (!m_WindowShouldClose) {
            start = SDL_GetTicksNS();
            GetVSync(vsync);
            frame_time = m_FrameRateLimit > 0 && vsync == 0 ? 1000000000 / m_FrameRateLimit : 0;
            if (SDL_PollEvent(&event)) {
                ImGui_ImplSDL3_ProcessEvent(&event);
                if (event.type == SDL_EVENT_QUIT)
                    m_WindowShouldClose = true;

                EventHandle(event);
            }
            // Render imgui
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
            RenderImgui(ImGui::GetIO());
            ImGui::Render();

            // Render behind imgui
            SDL_RenderClear(m_Backend.renderer_ptr);
            SDL_SetRenderDrawColor(m_Backend.renderer_ptr, 32, 32, 32, 255);
            Render(ImGui::GetIO().DeltaTime);
            // Finish render
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_Backend.renderer_ptr);
            SDL_RenderPresent(m_Backend.renderer_ptr);
            elapsed = SDL_GetTicksNS() - start;
            if (frame_time > 0 && frame_time > elapsed) {
                SDL_DelayPrecise(frame_time - elapsed);
            }
        }
    }
}

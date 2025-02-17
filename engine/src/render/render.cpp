#include "render/render.h"
#include "render/backend/sdl_imgui.h"
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
        return SDL_GL_SetSwapInterval(vsync);
    }

    bool RenderInterface::GetVSync(int &vsync) {
        return SDL_GL_GetSwapInterval(&vsync);
    }

    void RenderInterface::SetFrameRateLimit(int fps) {
        if (fps <= 0) fps = 0;
        m_FrameRateLimit = fps;
    }

    int RenderInterface::GetFrameRateLimit() {
        return m_FrameRateLimit;
    }

    const FSDL_Backend &RenderInterface::GetBackend() {
        return m_Backend;
    }

    void RenderInterface::m_Renderer() {
        glViewport(0, 0, 1024, 576);
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
                if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                    int w = 0, h = 0;
                    SDL_GetWindowSizeInPixels(m_Backend.window_ptr, &w, &h);
                    glViewport(0, 0, w, h);
                }
                EventHandle(event);
            }

            // Render imgui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            // Render behind imgui
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		    glClear(GL_COLOR_BUFFER_BIT);
            Render(ImGui::GetIO().DeltaTime);

            RenderImgui(ImGui::GetIO());
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            SDL_GL_SwapWindow(m_Backend.window_ptr);
            // Finish render
            elapsed = SDL_GetTicksNS() - start;
            if (frame_time > 0 && frame_time > elapsed) {
                SDL_DelayPrecise(frame_time - elapsed);
            }
        }
    }
}

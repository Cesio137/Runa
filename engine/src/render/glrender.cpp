#include "render/glrender.h"
#include "render/backend/sdl_imgui.h"

namespace Runa::Render {
    OpenglInterface::OpenglInterface(ESDL_GL_Driver driver) { Driver = driver; }

    OpenglInterface::~OpenglInterface() {
        SDL_GL_ImGuiDestroy();
        SDL_Quit();
    }

    int OpenglInterface::Exec() {
        int code = InitGLDriver(Backend, Driver);
        if (code != 0)
            return code;
        Renderer();
        return 0;
    }

    void OpenglInterface::CloseApp() {
        WindowShouldClose = true;
    }

    bool OpenglInterface::SetVSync(int value) {
        return SDL_GL_SetSwapInterval(value);
    }

    bool OpenglInterface::GetVSync(int &value) const {
        return SDL_GL_GetSwapInterval(&value);
    }

    void OpenglInterface::SetFrameRateLimit(int value) {
        if (value <= 0)
            value = 0;
        FrameRateLimit = value;
    }

    int OpenglInterface::GetFrameRateLimit() const {
        return FrameRateLimit;
    }

    FSDL_GL_Backend &OpenglInterface::GetBackend() {
        return Backend;
    }

    void OpenglInterface::Renderer() {
        glViewport(0, 0, 1024, 576);
        glEnable(GL_DEPTH_TEST);
        SDL_GL_ImGuiInit(Backend);
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
        while (!WindowShouldClose) {
            start = SDL_GetTicksNS();
            GetVSync(vsync);
            frame_time = FrameRateLimit > 0 && vsync == 0 ? 1000000000 / FrameRateLimit : 0;
            while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL3_ProcessEvent(&event);
                if (event.type == SDL_EVENT_QUIT)
                    WindowShouldClose = true;
                if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                    int w = 0, h = 0;
                    SDL_GetWindowSizeInPixels(Backend.window_ptr, &w, &h);
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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Render(ImGui::GetIO().DeltaTime);

            RenderImgui(ImGui::GetIO());
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SDL_GL_SwapWindow(Backend.window_ptr);
            // Finish render
            elapsed = SDL_GetTicksNS() - start;
            if (frame_time > 0 && frame_time > elapsed) {
                SDL_DelayPrecise(frame_time - elapsed);
            }
        }
    }
}

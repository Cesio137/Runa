#include "RenderInterface.h"
#include "Opengl/SDL_OpenglContext.h"
#include <iostream>

namespace Nanometro {

    RenderInterface::RenderInterface(uint32_t flags) { Flags = flags; }

    RenderInterface::~RenderInterface()
    {
        if (Flags == OPENGL_INIT_330 || Flags == OPENGL_INIT_460)
        {
            if (SDL_WasInit(SDL_INIT_VIDEO))
                SDL_ImGuiDestroy();
            Opengl.destroy();
        }
    }

    int RenderInterface::exec()
    {
        if (Flags == OPENGL_INIT_330 || Flags == OPENGL_INIT_460)
        {
            Opengl.init(Flags);
            if (Opengl.getErrorCode() == 0)
                Opengl_Render();
            return Opengl.getErrorCode();
        }

        return -1;
    }

    void RenderInterface::CloseApp()
    {
        WindowShouldClose = true;
    }

    std::pair<uint8_t, uint8_t> RenderInterface::GetOpenglVersion() const {
        return Opengl.version;
    }

    std::string RenderInterface::GetErrorLog() const {
        if (Flags == OPENGL_INIT_330 || Flags == OPENGL_INIT_460)
            return Opengl.getErrorMessage();

        return "";
    }

    void RenderInterface::Opengl_Render()
    {
        SDL_ImGuiInit(Opengl);
        PreInitialize(ImGui::GetIO());
        // Ready
        Ready();
        // Main loop
        SDL_Event event;
        while (!WindowShouldClose)
        {
            if (SDL_WaitEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    WindowShouldClose = true;
                
                EventHandle(event);
            }

            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            RenderImgui(ImGui::GetIO().DeltaTime);
            ImGui::Render();

            SDL_RenderClear(Opengl.renderer_ptr);
            SDL_SetRenderDrawColor(Opengl.renderer_ptr, 32, 32, 32, 255);
            // Render behind imgui
            Render(ImGui::GetIO().DeltaTime);
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), Opengl.renderer_ptr);
            // Render in front of imgui
            SDL_RenderPresent(Opengl.renderer_ptr);
        }
    }
}

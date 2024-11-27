#include "RenderInterface.h"
#include "Opengl/SDL_OpenglContext.h"
#include <iostream>

namespace Nanometro {

    RenderInterface::RenderInterface(uint8_t flags) { Flags = flags; }

    RenderInterface::~RenderInterface()
    {
        if (Flags == 0x21u || Flags == 0x2Eu)
        {   
            SDL_ImGuiDestroy();
            DestroyOpengl(Opengl);
        }
    }

    int RenderInterface::Exec()
    {
        if (Flags == 0x21u || Flags == 0x2Eu)
        {
            EOpenglVersion opengl_flags = static_cast<EOpenglVersion>(Flags);
            int code = InitOpengl(Opengl, opengl_flags);
            if (code) return code;
            Opengl_Render();
            return 0;
        }
        
        return 1;
    }

    void RenderInterface::CloseApp()
    {
        WindowShouldClose = true;
    }

    std::pair<uint8_t, uint8_t> RenderInterface::GetOpenglVersion() const {
        return Opengl.version;
    }

    std::string RenderInterface::GetErrorLog() const {
        if (Flags == 0x21u || Flags == 0x2Eu)
            return SDL_GetError();

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

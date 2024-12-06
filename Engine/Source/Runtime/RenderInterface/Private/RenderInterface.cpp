#include "RenderInterface.h"
#include "Backend/SDL_ImGui.h"
#include <iostream>

namespace Runa {

    RenderInterface::RenderInterface(ESDL_Driver driver) { Driver = driver; }

    RenderInterface::~RenderInterface()
    {
        SDL_ImGuiDestroy();
        SDL_Quit();
    }

    int RenderInterface::Exec()
    {
        int code = InitDriver(Backend, Driver);
        if (code) return code;
        Render();
        return 0;
    }

    void RenderInterface::CloseApp()
    {
        WindowShouldClose = true;
    }

    void RenderInterface::Render()
    {
        SDL_ImGuiInit(Backend);
        PreInitialize(ImGui::GetIO());
        // Ready
        Ready();
        // Main loop
        SDL_Event event;
        while (!WindowShouldClose)
        {
            if (SDL_WaitEvent(&event))
            {
                ImGui_ImplSDL3_ProcessEvent(&event);
                if (event.type == SDL_EVENT_QUIT)
                    WindowShouldClose = true;
                
                EventHandle(event);
            }

            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
            RenderImgui(ImGui::GetIO().DeltaTime);
            ImGui::Render();

            SDL_RenderClear(Backend.renderer_ptr);
            SDL_SetRenderDrawColor(Backend.renderer_ptr, 32, 32, 32, 255);
            // Render behind imgui
            Render(ImGui::GetIO().DeltaTime);
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Backend.renderer_ptr);
            // Render in front of imgui
            SDL_RenderPresent(Backend.renderer_ptr);
        }
    }
}

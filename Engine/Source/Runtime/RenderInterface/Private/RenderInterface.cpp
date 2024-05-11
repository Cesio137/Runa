#include "RenderInterface.h"
#include "Opengl/OpenglContext.h"
#include <iostream>

namespace Nanometro {

    RenderInterface::RenderInterface(uint32_t flags)
    {
        Flags = flags;
    }

    RenderInterface::~RenderInterface()
    {
        if (Flags == OPENGL_INIT_330 || Flags == OPENGL_INIT_460)
        {
            if (SDL_WasInit(SDL_INIT_VIDEO))
                Opengl_ImGuiDestroy();
            DestroyOpengl(SDL_Opengl);
        }
    }

    int RenderInterface::exec()
    {

        if (Flags == OPENGL_INIT_330 || Flags == OPENGL_INIT_460)
        {
            SDL_Opengl = ConstructOpengl(Flags);
            if (Opengl_GetError().code == 0)
                Opengl_Render();
            return Opengl_GetError().code;
        }

        return 0;
    }

    void RenderInterface::CloseApp()
    {
        WindowShouldClose = true;
    }

    uint32_t RenderInterface::GetFlags() const
    {
        return Flags;
    }

    std::pair<uint8_t, uint8_t> RenderInterface::GetOpenglVersion() const {
        return SDL_Opengl.Version;
    }

    std::string RenderInterface::GetGlsl() const {
        return SDL_Opengl.glsl_Version;
    }

    std::string RenderInterface::GetErrorLog() const {
        if (Flags == OPENGL_INIT_330 || Flags == OPENGL_INIT_460)
            return Opengl_GetError().log;

        return "";
    }

    void RenderInterface::Opengl_Render()
    {
        Opengl_ImGuiInit(SDL_Opengl);

        PreInitialize(ImGui::GetIO());
        // Ready
        Ready();

        // Main loop
        while (!WindowShouldClose)
        {
            SDL_Event SDL_event;
            SDL_WaitEvent(&SDL_event);
            ImGui_ImplSDL2_ProcessEvent(&SDL_event);
            if (SDL_event.type == SDL_WINDOWEVENT) {
                switch (SDL_event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        WindowShouldClose = true;
                    break;

                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        glViewport(0, 0, SDL_event.window.data1, SDL_event.window.data2); // Set viewport size

                }
            }
            EventHandle(SDL_event);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            // Specify the color of the background
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            // Clean the back buffer and assign the new color to it
            glClear(GL_COLOR_BUFFER_BIT);
            //emit render
            Render(ImGui::GetIO().DeltaTime);

            // UI Render
            RenderUI(ImGui::GetIO().DeltaTime);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap the back buffer with the front buffer
            SDL_GL_SwapWindow(SDL_Opengl.Window);
        }
    }
}

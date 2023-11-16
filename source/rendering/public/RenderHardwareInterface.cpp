//
// Created by natha on 09/11/2023.
//

#include "RenderHardwareInterface.h"

#include <thread>

RenderHardwareInterface::RenderHardwareInterface()
{
    Time = Timer();
}

void RenderHardwareInterface::CloseApp()
{
    WindowShouldClose = true;
}

int RenderHardwareInterface::Init(uint8_t flags)
{
    int code = 0;
    if (flags == 0)
    {
        code = SDLOpenGLManager();
    }

    return code;
}

int RenderHardwareInterface::SDLOpenGLManager()
{
    OpenGL = new SDL_OpenGL();

    string log;
    int error_code;

    if((error_code = OpenGL->GetErrorCode(log)) != 0)
    {
        OpenGL = nullptr;
        free(OpenGL);
        //emit on_error(error_code, log);
        return error_code;
    }

    OpenGL->SDL2_ImGui_Init();
    PreInitialize(ImGui::GetIO());
    RenderEngineSettings::LoadSettings();

    // Ready
    Ready();

    // Main loop
    while (!WindowShouldClose)
    {
        SDLOpenGLEventHandle();
        SDLOpenGLRender();
        FrameRateLock();
    }

    // Clean and finish
    OpenGL->SDL2_Destroy_OpenGL();
    OpenGL = nullptr;
    free(OpenGL);

    return 0;
}

void RenderHardwareInterface::SDLOpenGLEventHandle()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_WINDOWEVENT)
    {
        switch (event.window.event)
        {
            case SDL_WINDOWEVENT_CLOSE:
                WindowShouldClose = true;
                break;

            case SDL_WINDOWEVENT_SIZE_CHANGED:
                glViewport(0, 0, event.window.data1, event.window.data2); // Set viewport size

        }

    }
    EventHandle(event);
}

void RenderHardwareInterface::SDLOpenGLRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(OpenGL->GetWindow());
    ImGui::NewFrame();

    // Specify the color of the background
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    //emit render
    Render(ImGui::GetIO().DeltaTime);

    // UI Render
    RenderInterface(ImGui::GetIO().DeltaTime);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap the back buffer with the front buffer
    SDL_GL_SwapWindow(OpenGL->GetWindow());

}

void RenderHardwareInterface::FrameRateLock()
{
    if (RenderUserSettings::GetMaxFPS() == 0)
        return;
    
    double PreferredTime = 1000.0 / (RenderUserSettings::GetMaxFPS() + 1) ;
    PreferredTime = PreferredTime + SDL_GetTicks64();
    SDL_Delay(PreferredTime - SDL_GetTicks64());
}

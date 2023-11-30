//
// Created by natha on 09/11/2023.
//

#include "RenderHardwareInterface.h"

RenderHardwareInterface::RenderHardwareInterface()
{

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
    EngineUserSettings = new GameUserSettings();

    // Ready
    Ready();

    // Main loop
    while (!WindowShouldClose)
    {
        previousTicks = SDL_GetTicks64();
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
    switch (GameUserSettings::GetUpdateEventMode())
    {
        case 0:
            SDL_PollEvent(&event);
        break;
        case 1:
            SDL_WaitEvent(&event);
        break;

        default:
            SDL_PollEvent(&event);
        break;
    }
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

uint64_t RenderHardwareInterface::elapsedTime()
{

    return SDL_GetTicks64() - previousTicks;
}

void RenderHardwareInterface::FrameRateLock()
{
    if (GameUserSettings::GetFrameRateLimit() == 0)
        return;

    uint64_t PreferredTime = 1000 / (GameUserSettings::GetFrameRateLimit() + 1);
    if (PreferredTime > elapsedTime())
        SDL_Delay(PreferredTime - elapsedTime());
}



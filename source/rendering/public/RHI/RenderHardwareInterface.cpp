#include "RenderHardwareInterface.h"

RenderHardwareInterface::RenderHardwareInterface(QObject *parent)
        : QObject{parent}
{
    
}

int  RenderHardwareInterface::Init(Uint32 flags)
{
    if (flags == 0)
    {
        OpenGL = new SDL_OpenGL();
    }

    string log;
    int error_code;
#ifdef NANOMETRO_OPENGL_H

    if((error_code = OpenGL->GetErrorCode(log)) != 0)
    {
        OpenGL = nullptr;
        free(OpenGL);
        emit on_error(error_code, log);
        return error_code;
    }

    OpenGL->SDL2_ImGui_Init();
    PreInitialize(ImGui::GetIO());
    
    // Ready
    Ready();
    
    // Main loop
    while (!WindowShouldClose)
    {
        SDLEventHandle();
        SDLRender();
        FrameRateLock();
    }

    // Limpar e finalizar
    OpenGL->SDL2_Destroy_OpenGL();
    OpenGL = nullptr;
    free(OpenGL);

    return  0;
        
#endif
    
}

void RenderHardwareInterface::CloseApp()
{
    WindowShouldClose = true;
}

void RenderHardwareInterface::SDLEventHandle()
{
    SDL_Event event;
    SDL_WaitEvent(&event);
    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_WINDOWEVENT)
    {
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_CLOSE:
            WindowShouldClose = true;
            break;

        case SDL_WINDOWEVENT_SIZE_CHANGED:
#ifdef NANOMETRO_OPENGL_H
            glViewport(0, 0, event.window.data1, event.window.data2); // Set viewport size
#endif
            
        }
        
    }
    EventHandle(event);
}

void RenderHardwareInterface::SDLRender()
{
#ifdef NANOMETRO_OPENGL_H
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
#endif
}

void RenderHardwareInterface::FrameRateLock()
{
    float sleep = 0.0f;
    if ( QUserSettings::GetMaxFPS() == 0 || ImGui::GetIO().Framerate > float(QUserSettings::GetMaxFPS()) )
    {
        if ( ImGui::GetIO().Framerate > 500.0f )
        {
            sleep = 2.0f - ImGui::GetIO().DeltaTime;
            SDL_Delay(sleep);
        }
        
        return;
    }

    sleep = (1000.0f / float(QUserSettings::GetMaxFPS())) - ImGui::GetIO().DeltaTime;
    SDL_Delay(sleep);
}

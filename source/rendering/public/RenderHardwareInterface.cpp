#include "RenderHardwareInterface.h"

RenderHardwareInterface::RenderHardwareInterface(QObject *parent)
        : QObject{parent}
{
    
}

int  RenderHardwareInterface::Init(uint8_t flags)
{
    int code = 0;
    if (flags == 0)
    {
        code = SDLOpenGLManager();         
    }

    return  code;
}

void RenderHardwareInterface::CloseApp()
{
    WindowShouldClose = true;
}

int RenderHardwareInterface::SDLOpenGLManager()
{
    OpenGL = new SDL_OpenGL();
        
    QByteArray log;
    int error_code;

    if((error_code = OpenGL->GetErrorCode(log)) != 0)
    {
        OpenGL = nullptr;
        free(OpenGL);
        emit on_error(error_code, log);
        return error_code;
    }

    OpenGL->SDL2_ImGui_Init();
    PreInitialize(ImGui::GetIO());
    RenderingEngineSettings::LoadSettings();
    
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
    float sleep = 0.0;
    if ( RenderingUserSettings::GetMaxFPS() == 0 || ImGui::GetIO().Framerate > float(RenderingUserSettings::GetMaxFPS()) )
    {
        if ( ImGui::GetIO().Framerate > 500.0f )
        {
            sleep = 2.0f + ImGui::GetIO().DeltaTime;
            SDL_Delay(sleep);
        }
        return;
    }

    sleep = (1000.0f / float(RenderingUserSettings::GetMaxFPS())) + ImGui::GetIO().DeltaTime;
    SDL_Delay(sleep);
}

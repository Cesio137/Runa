#include "RenderHardwareInterface.h"

#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <thread>

#include <Rendering/Display.h>

Nanometro::RenderHardwareInterface::RenderHardwareInterface()
{

}

void Nanometro::RenderHardwareInterface::CloseApp()
{
    WindowShouldClose = true;
}

int Nanometro::RenderHardwareInterface::Init(uint8_t flags)
{
    int code = 0;
    RenderAPI = flags;
    if (flags == 0)
    {
        code = OpenGLManager();
    }
    /*
    else if (flags == 1)
    {
        code = GLFWOpenGLManager();
    }
    */
    return code;
}

int Nanometro::RenderHardwareInterface::OpenGLManager()
{
    SDL_Opengl = std::make_shared<Opengl>();
    int error_code = SDL_Opengl->GetErrorCode();

    if(error_code != 0)
    {
        //delete SDL_Opengl;
        //emit on_error(error_code, log);
        return error_code;
    }

    SDL_Opengl->Opengl_ImGuiInit();

    PreInitialize(ImGui::GetIO());
    EngineUserSettings = new GameUserSettings();
    Display::Context = SDL_Opengl->GetContext();
    Display::Window = SDL_Opengl->GetWindow();
    //SDL_GL_SetSwapInterval(1);

    // Ready
    Ready();

    // Main loop
    while (!WindowShouldClose)
    {
        PreviousTick = static_cast<long long int>( SDL_GetPerformanceCounter() );
        OpenGLEventHandle();
        OpenGLRender();
        FrameRateLock();
    }

    // Clean and finish
    //delete SDL_Opengl;
    delete EngineUserSettings;

    return 0;
}

void Nanometro::RenderHardwareInterface::OpenGLEventHandle()
{
    switch (GameUserSettings::GetUpdateEventMode())
    {
        case 0:
            SDL_PollEvent(&SDL_event);
        break;
        case 1:
            SDL_WaitEvent(&SDL_event);
        break;

        default:
            SDL_PollEvent(&SDL_event);
        break;
    }
    ImGui_ImplSDL2_ProcessEvent(&SDL_event);
    if (SDL_event.type == SDL_WINDOWEVENT)
    {
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
}

void Nanometro::RenderHardwareInterface::OpenGLRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Specify the color of the background
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    //emit render
    Render(WorldDeltaTime());

    // UI Render
    RenderInterface(WorldDeltaTime());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap the back buffer with the front buffer
    SDL_GL_SwapWindow(SDL_Opengl->GetWindow());

}

long long int Nanometro::RenderHardwareInterface::elapsedTime() const
{
    if (RenderAPI == 0)
    {
        return static_cast<long long int>( (SDL_GetPerformanceCounter() - PreviousTick) * 1000000000 / SDL_GetPerformanceFrequency() );
    }
    /*
    else if (RenderAPI == 1)
    {
        return static_cast<long long int>( glfwGetTime() * 1000000000 ) - PreviousTick;
    }
    */
    return 0;
}

double Nanometro::RenderHardwareInterface::WorldDeltaTime() const
{
    if (RenderAPI == 0)
    {
        return static_cast<double>(SDL_GetPerformanceCounter() - PreviousTick) / static_cast<double>(SDL_GetPerformanceFrequency());
    }
    return 0.0;
}

void Nanometro::RenderHardwareInterface::FrameRateLock()
{
    if (GameUserSettings::GetFrameRateLimit() == 0)
        return;

    long long int PreferredTime = 1000000000 / GameUserSettings::GetFrameRateLimit();
    if (PreferredTime > elapsedTime())
    {
        long long int nsTime = PreferredTime - elapsedTime();
        std::chrono::nanoseconds delta( nsTime );
        std::this_thread::sleep_for(delta);
    }
}

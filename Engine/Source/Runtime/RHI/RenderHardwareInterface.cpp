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
    else if (flags == 1)
    {
        code = GLFWOpenGLManager();
    }

    return code;
}

int RenderHardwareInterface::SDLOpenGLManager()
{
    SDL_OpenGL = new SDL();

    string log;
    int error_code;

    if((error_code = SDL_OpenGL->GetErrorCode(log)) != 0)
    {
        SDL_OpenGL = nullptr;
        free(SDL_OpenGL);
        //emit on_error(error_code, log);
        return error_code;
    }

    SDL_OpenGL->SDL2_ImGui_Init();
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
    SDL_OpenGL->SDL2_Destroy_OpenGL();
    SDL_OpenGL = nullptr;
    free(SDL_OpenGL);

    return 0;
}

void RenderHardwareInterface::SDLOpenGLEventHandle()
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
    EventHandle();
}

void RenderHardwareInterface::SDLOpenGLRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(SDL_OpenGL->GetWindow());
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
    SDL_GL_SwapWindow(SDL_OpenGL->GetWindow());

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

int RenderHardwareInterface::GLFWOpenGLManager()
{
    GLFW_OpenGL = new GLFW();

    string log;
    int error_code;

    if((error_code = GLFW_OpenGL->GetErrorCode(log)) != 0)
    {
        SDL_OpenGL = nullptr;
        free(SDL_OpenGL);
        //emit on_error(error_code, log);
        return error_code;
    }

    GLFW_OpenGL->GLFW_ImGui_Init();
    PreInitialize(ImGui::GetIO());
    EngineUserSettings = new GameUserSettings();

    // Ready
    Ready();

    // Main loop
    while (!glfwWindowShouldClose(GLFW_OpenGL->GetWindow()))
    {
        GLFWOpenGLEventHandle();
        GLFWOpenGLRender();
        FrameRateLock();
    }

    // Clean and finish
    GLFW_OpenGL->GLFW_Destroy_OpenGL();
    GLFW_OpenGL = nullptr;
    free(GLFW_OpenGL);

    return 0;
}

void RenderHardwareInterface::GLFWOpenGLEventHandle()
{
    glfwWaitEvents();
    EventHandle();
}

void RenderHardwareInterface::GLFWOpenGLRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
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
    glfwSwapBuffers(GLFW_OpenGL->GetWindow());
}



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
    RenderAPI = flags;
    if (flags == 0)
    {
        code = SDLOpenGLManager();
    }
    /*
    else if (flags == 1)
    {
        code = GLFWOpenGLManager();
    }
    */
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
    //SDL_GL_SetSwapInterval(1);

    // Ready
    Ready();

    // Main loop
    while (!WindowShouldClose)
    {
        PreviousTick = SDL_GetPerformanceCounter() * 1000000000 / SDL_GetPerformanceFrequency();
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
    EventHandle(SDL_event);
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

/*
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

    //glfwSwapInterval(1);

    // Ready
    Ready();

    // Main loop
    while (!glfwWindowShouldClose(GLFW_OpenGL->GetWindow()))
    {

        PreviousTick = static_cast<long long int>(1000000000 * glfwGetTime());
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
    glfwPollEvents();
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
*/

long long int RenderHardwareInterface::elapsedTime()
{
    if (RenderAPI == 0)
    {
        return static_cast<long long int>( SDL_GetPerformanceCounter() * 1000000000 / SDL_GetPerformanceFrequency() ) - PreviousTick;
    }
    /*
    else if (RenderAPI == 1)
    {
        return static_cast<long long int>( glfwGetTime() * 1000000000 ) - PreviousTick;
    }
    */
    return 0;
}

void RenderHardwareInterface::FrameRateLock()
{
    if (GameUserSettings::GetFrameRateLimit() == 0)
        return;

    long long int PreferredTime = 1000000000 / GameUserSettings::GetFrameRateLimit();
    if (PreferredTime > elapsedTime())
    {
        long long int nsTime = PreferredTime - elapsedTime();
        chrono::nanoseconds delta( nsTime );
        this_thread::sleep_for(delta);
    }
}



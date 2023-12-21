/*
#   Created by Nathan Miguel
*/

#ifdef HOST_SYSTEM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include "OpenGL.h"
#include <vector>

using namespace Nanometro;

SDL::SDL()
{
    /* Init SDL Video */
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        error_log = "SDL could not be initialized: ";
        error_log.append(SDL_GetError());
        error_code = SDL_INIT_VIDEO;
        return;
    }

    pair<uint8_t, uint8_t> GL_Version[13] =
            {
                     {4, 6},
                     {4, 5},
                     {4, 4},
                     {4, 3},
                     {4, 2},
                     {4, 1},
                     {4, 0},
                     {3, 3},
                     {3, 2},
                     {3, 1},
                     {3, 0},
                     {2, 1},
                     {2, 0}
            };

    if (AUTO_SELECT_OPENGL)
    {
        for (int i = 0; i < sizeof(GL_Version); i++)
        {
            if (GL_Version[i].first == OPENGL_MAJOR_VERSION && GL_Version[i].second < OPENGL_MINOR_VERSION)
            {
                error_log = "SDL could not create window: ";
                error_log.append(SDL_GetError());
                error_code = -1;
                SDL_Quit();
                return;
            }

            // Configurar atributos da janela OpenGL
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_Version[i].first);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_Version[i].second);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            // Create a GLFW window
            Window = SDL_CreateWindow(ENGINE_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (Window)
            {
                // Make the window's context current
                Context = SDL_GL_CreateContext(Window);
                if (!Context)
                {
                    error_log = "SDL could not create context: ";
                    error_log.append(SDL_GetError());
                    error_code = -1;
                    SDL_DestroyWindow(Window);
                    SDL_Quit();
                    return;
                }

                OpenGL_Version.first = GL_Version[i].first;
                OpenGL_Version.second = GL_Version[i].second;
                string glsl = "#version " + to_string(GL_Version[i].first) + to_string(GL_Version[i].second) + "0";
                glsl_Version = glsl.c_str();
                break;
            }
        }
    }
    else
    {
        // Configurar atributos da janela OpenGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        Window = SDL_CreateWindow(ENGINE_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        if (Window)
        {
            // Make the window's context current
            Context = SDL_GL_CreateContext(Window);
            if (!Context)
            {
                error_log = "SDL could not create context: ";
                error_log.append(SDL_GetError());
                error_code = -1;
                SDL_DestroyWindow(Window);
                SDL_Quit();
                return;
            }

            OpenGL_Version.first = OPENGL_MAJOR_VERSION;
            OpenGL_Version.second = OPENGL_MINOR_VERSION;
            glsl_Version = "#version " + to_string(OPENGL_MAJOR_VERSION) + to_string(OPENGL_MINOR_VERSION) + "0";
        }
        else
        {
            error_log = "SDL could not create window: ";
            error_log.append(SDL_GetError());
            error_code = -1;
            SDL_Quit();
            return;
        }
    }

    if ( !gladLoadGL( (GLADloadfunc)SDL_GL_GetProcAddress) )
    {
        error_log = "GLAD could not be loaded.";
        error_code = -1;
        SDL_DestroyWindow(Window);
        SDL_GL_DeleteContext(Context);
        SDL_Quit();
        return;
    }

    SDL_GL_SetSwapInterval(false);
}

SDL::~SDL()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    if (Context)
        SDL_GL_DeleteContext(Context);
    if (Window)
        SDL_DestroyWindow(Window);
    SDL_Quit();
}

void SDL::SDL2_ImGui_Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui_ImplSDL2_InitForOpenGL(Window, Context);
    ImGui_ImplOpenGL3_Init(glsl_Version.c_str());
}

int SDL::GetErrorCode(string &log)
{
    log = error_log;
    return error_code;
}

SDL_Window* SDL::GetWindow()
{
    return Window;
}

void SDL::SDL2_Destroy_OpenGL()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    if (Context)
        SDL_GL_DeleteContext(Context);
    if (Window)
        SDL_DestroyWindow(Window);
    SDL_Quit();
}

GLFW::GLFW()
{
    if(!glfwInit())
    {
        const char** description;
        glfwGetError(description);
        error_log = "GLFW could not be initialized: \n";
        for (int i = 0; i < (sizeof(description) / sizeof(description[0])); ++i)
        {
            error_log.append(description[i]);
        }
        error_code = GLFW_FALSE;
        return;
    }

    pair<uint8_t, uint8_t> GL_Version[13] =
            {
                    {4, 6},
                    {4, 5},
                    {4, 4},
                    {4, 3},
                    {4, 2},
                    {4, 1},
                    {4, 0},
                    {3, 3},
                    {3, 2},
                    {3, 1},
                    {3, 0},
                    {2, 1},
                    {2, 0}
            };

    if (AUTO_SELECT_OPENGL)
    {
        for (int i = 0; i < sizeof(GL_Version); i++)
        {
            if (GL_Version[i].first == OPENGL_MAJOR_VERSION && GL_Version[i].second < OPENGL_MINOR_VERSION)
            {
                const char** description;
                glfwGetError(description);
                error_log = "GLFW could not create window: \n";
                for (int i = 0; i < sizeof(description) / sizeof(description[0]); ++i)
                {
                    error_log.append(description[i]);
                }
                error_code = GLFW_FALSE;
                glfwTerminate();
                return;
            }

            // Configurar atributos da janela OpenGL
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_Version[i].first);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_Version[i].second);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // Create a GLFW window
            Window = glfwCreateWindow(1024, 576, ENGINE_NAME, NULL, NULL);
            if (Window)
            {
                // Make the window's context current
                glfwMakeContextCurrent(Window);

                OpenGL_Version.first = GL_Version[i].first;
                OpenGL_Version.second = GL_Version[i].second;
                string glsl = "#version " + to_string(GL_Version[i].first) + to_string(GL_Version[i].second) + "0";
                glsl_Version = glsl.c_str();
                SDL_GL_SetSwapInterval(false);
                break;
            }
        }
    }
    else
    {
        // Configurar atributos da janela OpenGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a GLFW window
        Window = glfwCreateWindow(1024, 576, ENGINE_NAME, NULL, NULL);

        if (Window)
        {
            // Make the window's context current
            glfwMakeContextCurrent(Window);

            OpenGL_Version.first = OPENGL_MAJOR_VERSION;
            OpenGL_Version.second = OPENGL_MINOR_VERSION;
            glsl_Version = "#version " + to_string(OPENGL_MAJOR_VERSION) + to_string(OPENGL_MINOR_VERSION) + "0";
            SDL_GL_SetSwapInterval(false);
        }
        else
        {
            const char** description;
            glfwGetError(description);
            error_log = "GLFW could not create window: \n";
            for (int i = 0; i < sizeof(description) / sizeof(description[0]); ++i)
            {
                error_log.append(description[i]);
            }
            error_code = GLFW_FALSE;
            glfwTerminate();
            return;
        }
    }

    // Load GLAD so it configures OpenGL
    if ( !gladLoadGL( (GLADloadfunc)glfwGetProcAddress) )
    {
        error_log = "GLAD could not be loaded.";
        error_code = -1;
        glfwDestroyWindow(Window);
        glfwTerminate();
        return;
    }

    glfwSwapInterval(0);
}

GLFW::~GLFW()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    if (Window)
        glfwDestroyWindow(Window);
    glfwTerminate();
}

void GLFW::GLFW_ImGui_Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init(glsl_Version.c_str());
}

void GLFW::GLFW_Destroy_OpenGL()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    if (Window)
        glfwDestroyWindow(Window);
    glfwTerminate();
}

int GLFW::GetErrorCode(string &log)
{
    log = error_log;
    return error_code;
}

GLFWwindow* GLFW::GetWindow()
{
    return Window;
}

#include "OpenGL/Opengl.h"
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <Renderer.h>
#include <Config.h>

Nanometro::Opengl::Opengl()
{
    /* Init SDL Video */
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        error_log = "SDL could not be initialized: ";
        error_log.append(SDL_GetError());
        error_code = SDL_INIT_VIDEO;
        return;
    }

    std::pair<uint8_t, uint8_t> GL_Version[13] =
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

                Version.first = GL_Version[i].first;
                Version.second = GL_Version[i].second;
                std::string glsl = "#version " + std::to_string(GL_Version[i].first) + std::to_string(GL_Version[i].second) + "0";
                glsl_Version = glsl;
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

            Version.first = OPENGL_MAJOR_VERSION;
            Version.second = OPENGL_MINOR_VERSION;
            glsl_Version = "#version " + std::to_string(OPENGL_MAJOR_VERSION) + std::to_string(OPENGL_MINOR_VERSION) + "0";
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
}

Nanometro::Opengl::~Opengl()
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

void Nanometro::Opengl::Opengl_ImGuiInit()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui_ImplSDL2_InitForOpenGL(Window, Context);
    ImGui_ImplOpenGL3_Init(glsl_Version.c_str());
}

void Nanometro::Opengl::Opengl_ImGuiDestroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

SDL_GLContext Nanometro::Opengl::GetContext()
{
    return Context;
}

SDL_Window* Nanometro::Opengl::GetWindow()
{
    return Window;
}

std::pair<uint8_t, uint8_t> Nanometro::Opengl::GetOpenglVersion()
{
    return Version;
}

std::string Nanometro::Opengl::GetGlslVersion()
{
    return glsl_Version;
}

int Nanometro::Opengl::GetErrorCode()
{
    return error_code;
}

std::string Nanometro::Opengl::GetErrorLog()
{
    return error_log;
}


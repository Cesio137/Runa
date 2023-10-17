//
// Created by natha on 10/10/2023.
//

#include "OpenGL.h"

SDL_OpenGL::SDL_OpenGL()
{
    /* Init SDL Video */
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        error_log = "SDL could not be initialized: ";
        error_log.append(SDL_GetError());
        error_code = SDL_INIT_VIDEO;
        return;
    }

    /* Select OGL Version */

    /* List GL Version */
    FPair GL_Version[13] =
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

    if (SDL_AUTO_SELECT_OPENGL)
    {   /* Autoselect */
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
            Window = SDL_CreateWindow("Nanometro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

                // Criar o renderizador com acelera��o de hardware
                Renderer = SDL_CreateRenderer(Window, 0, SDL_RENDERER_ACCELERATED);
                if (!Renderer)
                {
                    error_log = "SDL could not create renderer: ";
                    error_log.append(SDL_GetError());
                    error_code = -1;
                    SDL_DestroyWindow(Window);
                    SDL_GL_DeleteContext(Context);
                    SDL_Quit();
                    return;
                }

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
    {   /* Manual select */
        // Configurar atributos da janela OpenGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        Window = SDL_CreateWindow("Nanometro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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

            // Criar o renderizador com acelera��o de hardware
            Renderer = SDL_CreateRenderer(Window, 0, SDL_RENDERER_ACCELERATED);
            if (!Renderer)
            {
                error_log = "SDL could not create renderer: ";
                error_log.append(SDL_GetError());
                error_code = -1;
                SDL_DestroyWindow(Window);
                SDL_GL_DeleteContext(Context);
                SDL_Quit();
                return;
            }

            OpenGL_Version.first = OPENGL_MAJOR_VERSION;
            OpenGL_Version.second = OPENGL_MINOR_VERSION;
            glsl_Version = "#version " + FString::number(OPENGL_MAJOR_VERSION) + FString::number(OPENGL_MINOR_VERSION) + "0";

            SDL_GL_SetSwapInterval(false);
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

    //SDL_AddEventWatch(WindowEventWatcher, Window);
    // Load GLAD so it configures OpenGL
    if (!gladLoadGL())
    {
        error_log = "GLAD could not be loaded.";
        error_code = -1;
        SDL_DestroyWindow(Window);
        SDL_GL_DeleteContext(Context);
        SDL_DestroyRenderer(Renderer);
        SDL_Quit();
        return;
    }
    
}

SDL_OpenGL::~SDL_OpenGL()
{
    
}

void SDL_OpenGL::SDL2_ImGui_Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui_ImplSDL2_InitForOpenGL(Window, Context);
    ImGui_ImplOpenGL3_Init(glsl_Version.toUtf8());

    
}

void SDL_OpenGL::SDL2_Destroy_OpenGL()
{
    // Limpar e finalizar
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(Context);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

int SDL_OpenGL::GetErrorCode(FString &log)
{
    log = error_log;
    return error_code;
}

SDL_Window* SDL_OpenGL::GetWindow()
{
    return Window;
}

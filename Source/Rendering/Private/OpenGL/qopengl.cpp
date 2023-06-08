#include "qopengl.h"

QOpenGL* QOpenGL::opengl = nullptr;

QOpenGL::QOpenGL(QObject* parent)
        : QObject(parent)
{
    opengl = this;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        qDebug() << "SDL could not be initialized: " << SDL_GetError();
        return;
    }

    QList<QPair<int, int>> GL_Version =
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

    for (int i = 0; i < GL_Version.size(); i++)
    {
        if (GL_Version.at(i).first == OPENGL_MAJOR_VERSION && GL_Version.at(i).second < OPENGL_MINOR_VERSION)
        {
            qDebug() << "SDL could not create window: " << SDL_GetError();
            SDL_Quit();
            return;
        }

        // Configurar atributos da janela OpenGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_Version.at(i).first);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_Version.at(i).second);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        // Create a GLFW window
        Window = SDL_CreateWindow("Lumen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (Window)
        {
            // Make the window's context current
            Context = SDL_GL_CreateContext(Window);
            if (!Context)
            {
                qDebug() << "SDL could not create context: " << SDL_GetError();
                SDL_DestroyWindow(Window);
                SDL_Quit();
                return;
            }

            // Criar o renderizador com aceleração de hardware
            Renderer = SDL_CreateRenderer(Window, 0, SDL_RENDERER_ACCELERATED);
            if (!Renderer)
            {
                qDebug() << "SDL could not create renderer: " << SDL_GetError();
                SDL_Log("Falha ao criar o renderizador: %s", SDL_GetError());
                SDL_DestroyWindow(Window);
                SDL_GL_DeleteContext(Context);
                SDL_Quit();
                return;
            }

            OpenGL_Version.first = GL_Version.at(i).first;
            OpenGL_Version.second = GL_Version.at(i).second;
            glsl_Version = QString::number(GL_Version.at(i).first) + QString::number(GL_Version.at(i).second) + "0";
            viewportSize.first = 1024;
            viewportSize.second = 576;
            SDL_GL_SetSwapInterval(false);
            break;
        }
    }

    // Inicializar o GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SDL_Log("Falha ao inicializar o GLAD");
        qDebug() << "SDL could not initialize glad";
        SDL_GL_DeleteContext(Context);
        SDL_DestroyWindow(Window);
        SDL_Quit();
        return;
    }

    SDL_AddEventWatch(WindowEventWatcher, Window);
    // Load GLAD so it configures OpenGL
    gladLoadGL();
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    IO = &io;
    ImGui_ImplSDL2_InitForOpenGL(Window, Context);
    ImGui_ImplOpenGL3_Init("#version " + glsl_Version.toUtf8());
}

QOpenGL::~QOpenGL()
{
#ifdef GRAPHICS_API_OPENGL
#undef GRAPHICS_API_OPENGL
#endif
    delete IO;
}

void QOpenGL::Initialize()
{
    // Ready
    emit Ready(*IO);
    Time.start();
    // Main loop
    while (!WindowShouldClose)
    {
        Time.restart();
        EventHandle();
        Render();
        FrameRateLock();
    }

    // Limpar e finalizar
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(Context);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void QOpenGL::EventHandle()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            WindowShouldClose = true;
        }
    }
    if (WaitForEvents)
    {
        SDL_WaitEvent(&event);
    }
}

int QOpenGL::WindowEventWatcher(void* data, SDL_Event* event)
{
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED)
    {
        if (opengl->Window == (SDL_Window*)data)
        {
            opengl->Render();
        }
    }
    return 0;
}

void QOpenGL::SetMaxFrameRate(int framerate)
{
    MaxFrameRate = framerate;
}

void QOpenGL::FrameRateLock()
{
    if (MaxFrameRate == 0 || float(Time.elapsed()) > ( 1000.0f / float(MaxFrameRate)))
    {
        return;
    }

    float sleep = (1000.0f / float(MaxFrameRate)) - float(Time.elapsed());
    QThread::msleep(sleep);
}

void QOpenGL::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(Window);
    ImGui::NewFrame();
    // Renderização GUI
    emit RenderInterface(IO->DeltaTime);
    // Set viewport size
    glViewport(0, 0, viewportSize.first, viewportSize.second);
    // Specify the color of the background
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    emit Tick(IO->DeltaTime);

    // Swap the back buffer with the front buffer
    SDL_GL_SwapWindow(Window);
}

ImGuiIO &QOpenGL::GetIO()
{
    return *IO;
}

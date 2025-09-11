#include "render/sdl_glrender.h"

#include "handler/input.h"

namespace runa::render {
    int init_opengl(sdl_glbackend_t &backend, const sdl_gldriver_t driver) {
        /* Init SDL Video */
        if (!SDL_WasInit(SDL_INIT_VIDEO)) {
            if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
                return SDL_INIT_VIDEO;
        }

        // Configure driver
        switch (driver) {
            case sdl_gldriver_t::GL_DRIVER_OPENGLES:
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
                backend.glsl_version = "#version 320 es";
                break;
            case sdl_gldriver_t::GL_DRIVER_OPENGLCORE:
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
                backend.glsl_version = "#version 460";
                break;
            default:
                SDL_Quit();
                return 1;
        }

        // Create a SDL window
        backend.window_ptr = SDL_CreateWindow("Runa", 1024, 576, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (!backend.window_ptr) {
            SDL_Log("Failed to create window");
            return 1;
        }

        // Ensure window borders are visible on Wayland
        SDL_SetWindowBordered(backend.window_ptr, true);

        // Create a SDL renderer
        backend.gl_context = SDL_GL_CreateContext(backend.window_ptr);
        if (!backend.gl_context) {
            SDL_DestroyWindow(backend.window_ptr);
            SDL_Log("Failed to create context");
            return 1;
        }

        if (driver == GL_DRIVER_OPENGLES) {
            if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
                SDL_Log("Failed to initialize GLAD");
                SDL_DestroyWindow(backend.window_ptr);
                SDL_GL_DestroyContext(backend.gl_context);
                return 1;
            }
        }
        else {
            if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
                SDL_Log("Failed to initialize GLAD");
                SDL_DestroyWindow(backend.window_ptr);
                SDL_GL_DestroyContext(backend.gl_context);
                return 1;
            }
        }

        return 0;
    }

    void destroy_opengl(sdl_glbackend_t &backend) {
        if (backend.gl_context)
            SDL_GL_DestroyContext(backend.gl_context);
        if (backend.window_ptr)
            SDL_DestroyWindow(backend.window_ptr);
        backend.glsl_version.clear();
    }

    void gl_init_imgui(sdl_glbackend_t &backend) {
        if (!backend.window_ptr || !backend.gl_context)
            return;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui_ImplSDL3_InitForOpenGL(backend.window_ptr, backend.gl_context);
        ImGui_ImplOpenGL3_Init(backend.glsl_version.c_str());
    }

    void gl_destroy_imgui() {
        ImGui_ImplSDL3_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    sdl_glrender_c::sdl_glrender_c() {

    }

    sdl_glrender_c::~sdl_glrender_c() {

    }

    int sdl_glrender_c::run(const sdl_gldriver_t driver) {
        int code = 0;
        code = init_opengl(backend, driver);
        if (code != 0) return code;
        _render();
        return code;
    }

    void sdl_glrender_c::close_app() {
        window_should_close = true;
    }

    bool sdl_glrender_c::set_vsync(int value) {
        return SDL_GL_SetSwapInterval(value);
    }

    bool sdl_glrender_c::get_vsync(int *value) const {
        return SDL_GL_GetSwapInterval(value);
    }

    void sdl_glrender_c::set_framerate_limit(int value) {
        if (value <= 0) value = 0;
        framerate_limit = value;
    }

    int sdl_glrender_c::get_framerate_limit() const {
        return framerate_limit;
    }

    sdl_glbackend_t *sdl_glrender_c::get_backend() {
        return &backend;
    }

    void sdl_glrender_c::_render()
    {
        glViewport(0, 0, 1024, 576);
        glEnable(GL_DEPTH_TEST);
        gl_init_imgui(backend);
        init(ImGui::GetIO());
        // Framerate limit
        int vsync = 0;
        uint64_t start = 0;
        uint64_t elapsed = 0;
        uint64_t frame_time = 0;
        float delta = 0.0f;
        // Ready
        ready();
        // Main loop
        SDL_Event event;
        while (!window_should_close) {
            start = SDL_GetTicksNS();
            get_vsync(&vsync);
            frame_time = framerate_limit > 0 && vsync == 0 ? 1000000000 / framerate_limit : 0;
            while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL3_ProcessEvent(&event);
                if (event.type == SDL_EVENT_QUIT)
                    window_should_close = true;
                if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                    int w = 0, h = 0;
                    SDL_GetWindowSizeInPixels(backend.window_ptr, &w, &h);
                    glViewport(0, 0, w, h);
                }
                handler::input.update_event(event);
                eventhandle(event);
            }

            // Render imgui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            // Render behind imgui
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            elapsed = SDL_GetTicksNS() - start;
            delta = (float)((double)(elapsed) / 1000000000.0);
            render(delta);

            imguirender(ImGui::GetIO());
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SDL_GL_SwapWindow(backend.window_ptr);
            // Finish render
            elapsed = SDL_GetTicksNS() - start;
            if (frame_time > 0 && frame_time > elapsed) {
                SDL_DelayPrecise(frame_time - elapsed);
            }
        }
    }
}

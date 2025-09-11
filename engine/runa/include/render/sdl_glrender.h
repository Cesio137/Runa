#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <functional>

namespace runa::render {
    /*
    typedef enum {
        GL_DRIVER_NONE,
        GL_DRIVER_OPENGL,
        GL_DRIVER_OPENGLES,
        GL_DRIVER_VULKAN,
        GL_DRIVER_METAL,
        GL_DRIVER_DIRECT3D11,
        GL_DRIVER_DIRECT3D12,
        GL_DRIVER_WEBGL,
        GL_DRIVER_ANY,
    }sdl_gldriver_t;
    */

    typedef enum : uint8_t {
        GL_DRIVER_NONE = 0,
        GL_DRIVER_OPENGLCORE = 1,
        GL_DRIVER_OPENGLES = 2,
    }sdl_gldriver_t;

    typedef struct {
        SDL_Window *window_ptr;
        SDL_GLContext gl_context;
        std::string glsl_version;
    }sdl_glbackend_t;

    int init_opengl(sdl_glbackend_t &backend, const sdl_gldriver_t driver);
    void destroy_opengl(sdl_glbackend_t &backend);

    void gl_init_imgui(sdl_glbackend_t &backend);
    void gl_destroy_imgui();

    class sdl_glrender_c {
    public:
        sdl_glrender_c();
        ~sdl_glrender_c();

        virtual void init(ImGuiIO &io) {
            if (on_init)
                on_init(io);
        }

        virtual void ready() {
            if (on_ready)
                on_ready();
        }

        virtual void eventhandle(SDL_Event &event) {
            if (on_eventhandle)
                on_eventhandle(event);
        }

        virtual void imguirender(ImGuiIO &io) {
            if (on_imguirender)
                on_imguirender(io);
        }

        virtual void render(float delta) {
            if (on_render)
                on_render(delta);
        }

        /*Events*/
        std::function<void(ImGuiIO &)> on_init;
        std::function<void()> on_ready;
        std::function<void(SDL_Event &)> on_eventhandle;
        std::function<void(ImGuiIO &)> on_imguirender;
        std::function<void(float)> on_render;

        int run(const sdl_gldriver_t driver);
        void close_app();
        bool set_vsync(int value);
        bool get_vsync(int *value) const;
        void set_framerate_limit(int value);
        int get_framerate_limit() const;

        /*Backend*/
        sdl_glbackend_t *get_backend();

    private:
        /* SDL Events */
        bool window_should_close = false;
        
        int framerate_limit = 0;
        sdl_glbackend_t backend;

        void _render();
    };
}
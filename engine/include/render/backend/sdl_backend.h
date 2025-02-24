#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <utility>
#include <config.h>

namespace Runa::Render {
    enum ESDL_GL_Driver : uint8_t {
        CORE_320_ES = 0,
        CORE_460 = 1,
    };

    struct FSDL_GL_Backend {
        ~FSDL_GL_Backend() {
            if (gl_context)
                SDL_GL_DestroyContext(gl_context);
            if (window_ptr)
                SDL_DestroyWindow(window_ptr);
        }

        SDL_Window *window_ptr = nullptr;
        SDL_GLContext gl_context = nullptr;
        const char *glsl_version = "";
    };

    int InitGLDriver(FSDL_GL_Backend &backend, ESDL_GL_Driver driver = ESDL_GL_Driver::CORE_460);
}

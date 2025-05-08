#include "render/backend/sdl_backend.h"
#include <iostream>
#include <EASTL/unique_ptr.h>

namespace Runa::Render {
    int InitGLDriver(FSDL_GL_Backend &backend, ESDL_GL_Driver driver) {
        /* Init SDL Video */
        if (!SDL_WasInit(SDL_INIT_VIDEO)) {
            if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
                return SDL_INIT_VIDEO;
        }

        // Configure driver
        switch (driver) {
            case ESDL_GL_Driver::CORE_320_ES:
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
                backend.glsl_version = "#version 320 es";
                break;
            case ESDL_GL_Driver::CORE_460:
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
        backend.window_ptr = SDL_CreateWindow(ENGINE_NAME, 1024, 576, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (!backend.window_ptr) {
            SDL_Log("Failed to create window");
            return 1;
        }

        // Create a SDL renderer
        backend.gl_context = SDL_GL_CreateContext(backend.window_ptr);
        if (!backend.gl_context) {
            SDL_DestroyWindow(backend.window_ptr);
            SDL_Log("Failed to create context");
            return 1;
        }

        if (driver == CORE_320_ES) {
            if (!gladLoadGLES2Loader((GLADloadproc) SDL_GL_GetProcAddress)) {
                SDL_Log("Failed to initialize GLAD");
                SDL_DestroyWindow(backend.window_ptr);
                SDL_GL_DestroyContext(backend.gl_context);
                return 1;
            }
        }
        else {
            if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
                SDL_Log("Failed to initialize GLAD");
                SDL_DestroyWindow(backend.window_ptr);
                SDL_GL_DestroyContext(backend.gl_context);
                return 1;
            }
        }

        return 0;
    }
}

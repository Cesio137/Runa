#pragma once

#include <Config.h>
#include <SDL3/SDL.h>
#include <string>

namespace Runa {
    enum ESDL_Driver : uint8_t {
        ES_320 = 0,
        CORE_330 = 1,
        CORE_460 = 2,
        VULKAN = 3,
        D3D11 = 4,
        D3D12 = 5,
    };

    struct FSDL_Backend {
        ~FSDL_Backend() {
            if (renderer_ptr)
                SDL_DestroyRenderer(renderer_ptr);
            if (window_ptr)
                SDL_DestroyWindow(window_ptr);
        }

        SDL_Window *window_ptr;
        SDL_Renderer *renderer_ptr;
    };

    inline int InitDriver(FSDL_Backend &backend, ESDL_Driver driver = ESDL_Driver::CORE_330) {
        /* Init SDL Video */
        if (!SDL_WasInit(SDL_INIT_VIDEO)) {
            if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
                return SDL_INIT_VIDEO;
        }

        // Configure driver
        const char *driver_name = "";
        switch (driver) {
            case ESDL_Driver::CORE_330:
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
                driver_name = "opengl";
                break;
            case ESDL_Driver::CORE_460:
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
                driver_name = "opengl";
                break;
            default:
                SDL_Quit();
                return 1;
        }

        // Create a SDL window
        backend.window_ptr = SDL_CreateWindow(ENGINE_NAME, 1024, 576, SDL_WINDOW_RESIZABLE);
        if (!backend.window_ptr)
            return 1;

        // Create a SDL renderer
        backend.renderer_ptr = SDL_CreateRenderer(backend.window_ptr, driver_name);
        if (!backend.renderer_ptr)
            return 1;

        return 0;
    }

    inline std::pair<uint8_t, uint8_t> GetLatestOpenglVersionSupported() {
        std::pair<uint8_t, uint8_t> version;

        /* Init SDL Video */
        bool bWasInit = SDL_WasInit(SDL_INIT_VIDEO);
        if (!bWasInit)
            if (SDL_InitSubSystem(SDL_INIT_VIDEO))
                return version;

        std::pair<uint8_t, uint8_t> GL_Version[13] = {
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

        for (int i = 0; i < sizeof(GL_Version); i++) {
            // Configure opengl attributes
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_Version[i].first);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_Version[i].second);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // Create a SDL window
            SDL_Window *_window = SDL_CreateWindow("LastOpenglVersionSupported", 1024, 576,
                                                   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (_window) {
                version.first = GL_Version[i].first;
                version.second = GL_Version[i].second;
                SDL_DestroyWindow(_window);
                break;
            }
        }

        if (bWasInit)
            SDL_Quit();

        return version;
    }
}

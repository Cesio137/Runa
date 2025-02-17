#pragma once

#include "render/backend/sdl_backend.h"

namespace Runa
{
    int InitDriver(FSDL_Backend &backend, ESDL_Driver driver)
    {
        /* Init SDL Video */
        if (!SDL_WasInit(SDL_INIT_VIDEO))
        {
            if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
                return SDL_INIT_VIDEO;
        }

        // Configure driver
        const char *driver_name = "";
        switch (driver)
        {
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
        backend.window_ptr = SDL_CreateWindow(ENGINE_NAME, 1024, 576, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (!backend.window_ptr)
            return 1;

        // Create a SDL renderer
        backend.gl_context = SDL_GL_CreateContext(backend.window_ptr);
        if (!backend.gl_context)
            return 1;

        if (!gladLoaderLoadGL())
            return 1;

        return 0;
    }

    std::pair<uint8_t, uint8_t> GetLatestOpenglVersionSupported()
    {
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

        for (int i = 0; i < sizeof(GL_Version); i++)
        {
            // Configure opengl attributes
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_Version[i].first);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_Version[i].second);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // Create a SDL window
            SDL_Window *_window = SDL_CreateWindow("LastOpenglVersionSupported", 1024, 576,
                                                   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (_window)
            {
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

#pragma once

#include <Config.h>
#include <SDL3/SDL.h>
#include <string>

namespace Nanometro
{
    enum EOpenglVersion : uint8_t
    {
        ES_320 = 0x20u,
        CORE_330 = 0x21u,
        CORE_460 = 0x2Eu
    };

    struct FSDL_Opengl
    {
        SDL_Window *window_ptr;
        SDL_Renderer *renderer_ptr;
        std::pair<uint8_t, uint8_t> version;
    };

    inline int InitOpengl(FSDL_Opengl &opengl, EOpenglVersion version = EOpenglVersion::CORE_330)
    {
        /* Init SDL Video */
        if (!SDL_WasInit(SDL_INIT_VIDEO))
        {
            if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
                return SDL_INIT_VIDEO;
        }

        // Configure oepngl attribute
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        if (version == EOpenglVersion::CORE_460)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
            opengl.version.first = 4;
            opengl.version.second = 6;
        }
        else if (version == EOpenglVersion::CORE_330)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            opengl.version.first = 3;
            opengl.version.second = 3;
        }

        // Create a SDL window
        opengl.window_ptr = SDL_CreateWindow(ENGINE_NAME, 1024, 576, SDL_WINDOW_RESIZABLE);
        if (!opengl.window_ptr)
            return 1;

        opengl.renderer_ptr = SDL_CreateRenderer(opengl.window_ptr, "opengl");
        if (!opengl.renderer_ptr)
            return 1;

        return 0;
    }

    inline void DestroyOpengl(FSDL_Opengl &opengl)
    {
        if (opengl.renderer_ptr)
            SDL_DestroyRenderer(opengl.renderer_ptr);
        if (opengl.window_ptr)
            SDL_DestroyWindow(opengl.window_ptr);
        opengl.version.first = 0;
        opengl.version.second = 0;
        SDL_Quit();
    }

    inline std::pair<uint8_t, uint8_t> GetLatestOpenglVersionSupported()
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
            {2, 0}};

        for (int i = 0; i < sizeof(GL_Version); i++)
        {
            // Configure opengl attributes
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_Version[i].first);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_Version[i].second);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // Create a SDL window
            SDL_Window *_window = SDL_CreateWindow("LastOpenglVersionSupported", 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

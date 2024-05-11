#pragma once

#ifndef OPENGL_H
#define OPENGL_H

#include <Config.h>
#include <SDL.h>
#include <string>

#define OPENGL_INIT_330 0x00000330u
#define OPENGL_INIT_460 0x00000460u

namespace Nanometro
{

    struct Opengl {
        SDL_Window* Window;
        SDL_GLContext Context;
        std::pair<uint8_t, uint8_t> Version;
        char glsl_Version[13];
    };

    inline std::pair<uint8_t, uint8_t> GetLastOpenglVersionSupported()
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
            SDL_Window* _window = SDL_CreateWindow(ENGINE_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (_window)
            {
                // Make the window's context current
                SDL_GLContext _context = SDL_GL_CreateContext(_window);
                if (_context)
                {
                    version.first = GL_Version[i].first;
                    version.second = GL_Version[i].second;
                    SDL_DestroyWindow(_window);
                    SDL_GL_DeleteContext(_context);
                    break;
                }
                else{ SDL_DestroyWindow(_window); }

            }
        }

        if (bWasInit)
            SDL_Quit();

        return version;
    }

}

#endif //OPENGL_H

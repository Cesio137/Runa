#ifndef SDL_OPENGL_H
#define SDL_OPENGL_H

#include <SDL.h>
#include <string>

#define OPENGL_INIT_330 0x00000330u
#define OPENGL_INIT_460 0x00000460u

namespace Nanometro
{

    struct SDL_Opengl {
        SDL_Window* window_ptr;
        SDL_Renderer* renderer_ptr;
        std::pair<uint8_t, uint8_t> version;
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
            SDL_Window* _window = SDL_CreateWindow("LastOpenglVersionSupported", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

#endif //SDL_OPENGL_H

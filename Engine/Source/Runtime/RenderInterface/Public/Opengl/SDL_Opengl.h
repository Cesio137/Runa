#pragma once

#include <Config.h>
#include <SDL.h>
#include <string>

#define OPENGL_INIT_330 0x00000330u
#define OPENGL_INIT_460 0x00000460u

namespace Nanometro
{

    struct FSDL_Opengl {
    public:
        ~FSDL_Opengl() { destroy(); }

        SDL_Window* window_ptr;
        SDL_Renderer* renderer_ptr;
        std::pair<uint8_t, uint8_t> version;

        bool init(uint32_t flags) {
            /* Init SDL Video */
            if (!SDL_WasInit(SDL_INIT_VIDEO))
            {
                if (SDL_InitSubSystem(SDL_INIT_VIDEO))
                {
                    error_code = SDL_INIT_VIDEO;
                    error_message = "SDL Video Subsystem could not be initialized: ";
                    error_message.append(SDL_GetError());
                    return false;
                }
            }

            // Configure oepngl attribute
            if (flags == OPENGL_INIT_460)
            {
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
                version.first = 4;
                version.second = 6;
            }
            else if (flags == OPENGL_INIT_330)
            {
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
                version.first = 3;
                version.second = 3;
            }
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // Create a SDL window
            window_ptr = SDL_CreateWindow(ENGINE_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (!window_ptr)
            {
                error_code = -1;
                if (flags == OPENGL_INIT_460)
                    error_message = "SDL could not create window using opengl 460: ";
                else if (flags == OPENGL_INIT_330)
                    error_message = "SDL could not create window using opengl 330: ";
                error_message.append(SDL_GetError());
                destroy();
                return false;
            }

            renderer_ptr = SDL_CreateRenderer(window_ptr, -1, 0);
            if (!renderer_ptr)
            {
                error_code = -2;
                error_message = "SDL could not create renderer: ";
                error_message.append(SDL_GetError());
                destroy();
                return false;
            }
        }

        void destroy() {
            if (renderer_ptr)
                SDL_DestroyRenderer(renderer_ptr);
            if (window_ptr)
                SDL_DestroyWindow(window_ptr);
            version.first = 0;
            version.second = 0;
            SDL_Quit();
        }

        std::string getErrorMessage() const { return error_message; }
        int getErrorCode() const { return error_code; }

    private:
        std::string error_message;
        int error_code;
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

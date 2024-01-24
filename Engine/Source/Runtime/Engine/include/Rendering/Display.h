#pragma once

#include <SDL.h>

namespace Nanometro
{
    class Display
    {
        friend class RenderHardwareInterface;
    public:
        static SDL_Window* GetWindow();
        static SDL_GLContext GetContext();

    private:
        inline static SDL_Window* Window = nullptr;
        inline static SDL_GLContext Context = nullptr;
    };
}
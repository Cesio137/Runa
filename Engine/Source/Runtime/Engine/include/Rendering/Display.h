#pragma once

#include <memory>
#include <SDL.h>

namespace Nanometro
{
    class Display
    {
        friend class RenderHardwareInterface;
    public:
        static std::shared_ptr<SDL_Window> GetWindow();
        static SDL_GLContext GetContext();

    private:
        inline static std::shared_ptr<SDL_Window> Window;
        inline static SDL_GLContext Context;
    };
}
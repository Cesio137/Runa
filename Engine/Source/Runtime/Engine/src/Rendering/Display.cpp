#include "Rendering/Display.h"

std::shared_ptr<SDL_Window> Nanometro::Display::GetWindow()
{
    return Window;
}

SDL_GLContext Nanometro::Display::GetContext()
{
    return Context;
}

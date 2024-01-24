#include "Rendering/Display.h"

SDL_Window *Nanometro::Display::GetWindow()
{
    return Window;
}

SDL_GLContext Nanometro::Display::GetContext()
{
    return Context;
}

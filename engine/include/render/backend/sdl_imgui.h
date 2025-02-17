#pragma once

#include "render/backend/sdl_backend.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <imgui_impl_opengl3.h>

namespace Runa
{
    void SDL_ImGuiInit(FSDL_Backend &backend);
    void SDL_ImGuiDestroy();
}
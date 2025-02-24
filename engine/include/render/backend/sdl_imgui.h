#pragma once

#include "render/backend/sdl_backend.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

namespace Runa::Render {
    void SDL_GL_ImGuiInit(FSDL_GL_Backend &backend);
    void SDL_GL_ImGuiDestroy();
}

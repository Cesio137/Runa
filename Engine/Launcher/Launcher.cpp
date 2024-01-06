#include "Launcher.h"

Nanometro::Launcher::Launcher()
{

}

Nanometro::Launcher::~Launcher()
{

}

void Nanometro::Launcher::PreInitialize(ImGuiIO &io)
{
    RenderHardwareInterface::PreInitialize(io);
    GameUserSettings::SetFrameRateLimit(60);
}

void Nanometro::Launcher::Ready()
{
    RenderHardwareInterface::Ready();
}

void Nanometro::Launcher::EventHandle(SDL_Event event)
{
    RenderHardwareInterface::EventHandle(event);
}

void Nanometro::Launcher::RenderInterface(float delta)
{
    RenderHardwareInterface::RenderInterface(delta);

    ImGui::Begin("Framerate");
    ImGui::Text(std::to_string(ImGui::GetIO().Framerate).c_str());
    ImGui::End();
}

void Nanometro::Launcher::Render(float delta)
{
    RenderHardwareInterface::Render(delta);
}

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

void Nanometro::Launcher::RenderInterface(double delta)
{
    RenderHardwareInterface::RenderInterface(delta);

    ImGui::Begin("Framerate");
    auto test = static_cast<float>(delta);
    ImGui::Text("%f", test);
    ImGui::End();
}

void Nanometro::Launcher::Render(double delta)
{
    RenderHardwareInterface::Render(delta);
}

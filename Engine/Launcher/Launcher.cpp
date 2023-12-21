#include "Launcher.h"

Launcher::Launcher()
{

}

Launcher::~Launcher()
{

}

void Launcher::PreInitialize(ImGuiIO &io)
{
    RenderHardwareInterface::PreInitialize(io);
}

void Launcher::Ready()
{
    RenderHardwareInterface::Ready();
}

void Launcher::EventHandle()
{
    RenderHardwareInterface::EventHandle();
}

void Launcher::RenderInterface(float delta)
{
    RenderHardwareInterface::RenderInterface(delta);
}

void Launcher::Render(float delta)
{
    RenderHardwareInterface::Render(delta);
}

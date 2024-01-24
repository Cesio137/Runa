#pragma once

#include <RenderHardwareInterface.h>

namespace Nanometro
{
    class Launcher : public RenderHardwareInterface
    {
    public:
        Launcher();
        ~Launcher();

        void PreInitialize(ImGuiIO &io) override;
        void Ready() override;
        void EventHandle(SDL_Event event) override;
        void RenderInterface(double delta) override;
        void Render(double delta) override;

    private:
        ImGuiWindowFlags winFlags;
    };
}
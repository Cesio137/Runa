#pragma once

#include <RenderHardwareInterface.h>

namespace Nanometro
{
    class Launcher : RenderHardwareInterface
    {
    public:
        Launcher();
        ~Launcher();

        void PreInitialize(ImGuiIO &io) override;
        void Ready() override;
        void EventHandle() override;
        void RenderInterface(float delta) override;
        void Render(float delta) override;
    };
}
#pragma once

#include <CoreMinimal.h>
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
        void RenderInterface(float delta) override;
        void Render(float delta) override;

    private:
        ImGuiWindowFlags winFlags;
    };
}
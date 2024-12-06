#pragma once

#include "Backend/SDL_Backend.h"
#include <imgui.h>

namespace Runa
{

    class RenderInterface
    {
    public:
        RenderInterface(ESDL_Driver driver = ESDL_Driver::CORE_330);
        ~RenderInterface();

        virtual void PreInitialize(ImGuiIO &io) {}
        virtual void Ready() {}
        virtual void EventHandle(SDL_Event event) {};
        virtual void RenderImgui(double delta) {}
        virtual void Render(double delta) {}

        /*Application*/
        int Exec();
        void CloseApp();

    private:
        /* Flags */
        ESDL_Driver Driver;

        /* SDL */
        FSDL_Backend Backend;
        void Render();
        /* SDL Events */
        bool WindowShouldClose = false;
    };

} // Nanometro

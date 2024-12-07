#pragma once

#include <functional>

#include "Backend/SDL_Backend.h"
#include <imgui.h>

namespace Runa
{

    class RenderInterface
    {
    public:
        RenderInterface(ESDL_Driver driver = ESDL_Driver::CORE_330);
        ~RenderInterface();

        virtual void PreInitialize(ImGuiIO &io) {
            if (OnPreInitialize) OnPreInitialize(io);
        }
        virtual void Ready() {
            if (OnReady) OnReady();
        }
        virtual void EventHandle(SDL_Event event) {
            if (OnEventHandle) OnEventHandle(event);
        }
        virtual void RenderImgui(ImGuiIO &io) {
            if (OnRenderImgui) OnRenderImgui(io);
        }
        virtual void Render(float delta) {
            if (OnRender) OnRender(delta);
        }

        /*Application*/
        int Exec();
        void CloseApp();
        bool SetVSync(int vsync);
        bool GetVSync(int &vsync);
        void SetFrameRateLimit(int fps);
        int GetFrameRateLimit();

        /*Backend*/
        const FSDL_Backend *GetBackend();

        /*Events*/
        std::function<void(ImGuiIO &)> OnPreInitialize;
        std::function<void()> OnReady;
        std::function<void(SDL_Event)> OnEventHandle;
        std::function<void(ImGuiIO &)> OnRenderImgui;
        std::function<void(float)> OnRender;

    private:
        /* Flags */
        ESDL_Driver m_Driver;

        /*Application*/
        int m_FrameRateLimit = 0;
        int m_GetSwapInterval(const char* name);

        /* SDL */
        FSDL_Backend m_Backend;
        void m_Renderer();
        /* SDL Events */
        bool m_WindowShouldClose = false;
    };

} // Nanometro

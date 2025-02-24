#pragma once

#include "render/backend/sdl_backend.h"
#include <functional>
#include <imgui.h>

namespace Runa::Render {
    class OpenglInterface {
    public:
        OpenglInterface(ESDL_GL_Driver driver = ESDL_GL_Driver::CORE_460);
        ~OpenglInterface();

        virtual void PreInitialize(ImGuiIO &io) {
            if (OnPreInitialize)
                OnPreInitialize(io);
        }

        virtual void Ready() {
            if (OnReady)
                OnReady();
        }

        virtual void EventHandle(SDL_Event event) {
            if (OnEventHandle)
                OnEventHandle(event);
        }

        virtual void RenderImgui(ImGuiIO &io) {
            if (OnRenderImgui)
                OnRenderImgui(io);
        }

        virtual void Render(float delta) {
            if (OnRender)
                OnRender(delta);
        }

        /*Application*/
        int Exec();
        void CloseApp();
        bool SetVSync(int value);
        bool GetVSync(int &value) const;
        void SetFrameRateLimit(int value);
        int GetFrameRateLimit() const;

        /*Backend*/
        FSDL_GL_Backend &GetBackend();

        /*Events*/
        std::function<void(ImGuiIO &)> OnPreInitialize;
        std::function<void()> OnReady;
        std::function<void(SDL_Event)> OnEventHandle;
        std::function<void(ImGuiIO &)> OnRenderImgui;
        std::function<void(float)> OnRender;

    private:
        /* Flags */
        ESDL_GL_Driver Driver;

        /*Application*/
        int FrameRateLimit = 0;

        /* SDL */
        FSDL_GL_Backend Backend;

        void Renderer();

        /* SDL Events */
        bool WindowShouldClose = false;
    };
} // Nanometro

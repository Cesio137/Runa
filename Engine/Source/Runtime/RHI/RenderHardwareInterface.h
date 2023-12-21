#pragma once

#include <OpenGL/OpenGL.h>
#include <GameFramework/GameUserSettings.h>

namespace Nanometro
{

    class RenderHardwareInterface
    {
    public:
        explicit RenderHardwareInterface();
        int Init(uint8_t flags);

        virtual void PreInitialize(ImGuiIO& io){}
        virtual void Ready(){}
        virtual void EventHandle(){}
        virtual void RenderInterface(float delta){}
        virtual void Render(float delta){}

        GameUserSettings* EngineUserSettings;
        SDL_Event SDL_event;

        /*Application*/
        void CloseApp();

    private:
        /*Graphics API*/
        SDL *SDL_OpenGL = nullptr;
        int SDLOpenGLManager();
        void SDLOpenGLEventHandle();
        void SDLOpenGLRender();

        /*Graphics API*/
        GLFW *GLFW_OpenGL = nullptr;
        int GLFWOpenGLManager();
        void GLFWOpenGLEventHandle();
        void GLFWOpenGLRender();

        /*SDL Events*/
        bool WindowShouldClose = false;

        /*Performance*/
        uint64_t previousTicks;
        uint64_t elapsedTime();
        void FrameRateLock();

    };

}

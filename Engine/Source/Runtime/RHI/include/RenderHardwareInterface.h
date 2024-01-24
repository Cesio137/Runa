#pragma once

#include <Renderer.h>
#include <iostream>
#include <GameFramework/GameUserSettings.h>
#include <chrono>
#include <thread>

namespace Nanometro
{

    class RenderHardwareInterface
    {
    public:
        explicit RenderHardwareInterface();
        int Init(uint8_t flags);

        virtual void PreInitialize(ImGuiIO& io){}
        virtual void Ready(){}
        virtual void EventHandle(SDL_Event event){}
        virtual void RenderInterface(double delta){}
        virtual void Render(double delta){}


        SDL_Event SDL_event;

        /*Application*/
        void CloseApp();

    private:
        /*Graphics API SDL*/
        uint8_t RenderAPI = 0; 
        //SDL
        OpenGL *SDL_OpenGL = nullptr;
        int OpenGLManager();
        void OpenGLEventHandle();
        void OpenGLRender();
        /*SDL Events*/
        bool WindowShouldClose = false;

        /*Performance*/
        GameUserSettings* EngineUserSettings;
        long long int PreviousTick;
        double WorldDeltaTime() const;
        long long int elapsedTime() const;
        void FrameRateLock();

    };

}

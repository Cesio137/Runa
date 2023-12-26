#pragma once

#include <CoreMinimal.h>
#include <iostream>
#include <OpenGL/OpenGL.h>
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
        virtual void RenderInterface(float delta){}
        virtual void Render(float delta){}

        GameUserSettings* EngineUserSettings;
        SDL_Event SDL_event;

        /*Application*/
        void CloseApp();

    private:
        /*Graphics API SDL*/
        uint8_t RenderAPI = 0; 
        //SDL
        SDL *SDL_OpenGL = nullptr;
        int SDLOpenGLManager();
        void SDLOpenGLEventHandle();
        void SDLOpenGLRender();
        /*SDL Events*/
        bool WindowShouldClose = false;

        //GLFW
        /*
        GLFW *GLFW_OpenGL = nullptr;
        int GLFWOpenGLManager();
        void GLFWOpenGLEventHandle();
        void GLFWOpenGLRender();
        */

        /*Performance*/
        long long int PreviousTick;
        long long int elapsedTime();
        void FrameRateLock();

    };

}

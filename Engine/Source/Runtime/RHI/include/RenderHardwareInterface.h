#pragma once

#include <memory>
#include <Opengl/Opengl.h>
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
        std::shared_ptr<Opengl> SDL_Opengl;
        int OpenGLManager();
        void OpenGLEventHandle();
        void OpenGLRender();
        /*SDL Events*/
        bool WindowShouldClose = false;

        /*Performance*/
        std::shared_ptr<GameUserSettings> EngineUserSettings;
        long long int PreviousTick;
        double WorldDeltaTime() const;
        long long int elapsedTime() const;
        void FrameRateLock();

    };

}

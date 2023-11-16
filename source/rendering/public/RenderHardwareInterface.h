#ifndef RENDERHARDWAREINTERFACE_H
#define RENDERHARDWAREINTERFACE_H

#include <OpenGL/OpenGL.h>
#include <RenderSettings/RenderEngineSettings.h>
#include <RenderSettings/RenderUserSettings.h>
#include <Timer/Timer.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

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

    /*Performance*/
    Timer Time;

    /*Application*/
    void CloseApp();
    
private:
    /*Graphics API*/
    SDL_OpenGL *OpenGL = nullptr;
    int SDLOpenGLManager();
    void SDLOpenGLEventHandle();
    void SDLOpenGLRender();

    /*SDL Events*/
    bool WindowShouldClose = false;

    /*Performance*/
    void FrameRateLock();

};



#endif // RHI_H

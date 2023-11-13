#ifndef RENDERHARDWAREINTERFACE_H
#define RENDERHARDWAREINTERFACE_H

#include <OpenGL/OpenGL.h>
#include <RenderSettings/RenderEngineSettings.h>
#include <RenderSettings/RenderUserSettings.h>

using namespace std;

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
    double PreviousTime;
    void FrameRateLock();

};

#endif // RHI_H

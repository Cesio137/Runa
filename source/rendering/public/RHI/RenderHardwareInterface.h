#ifndef RHI_H
#define RHI_H

#include <QObject>
#include <opengl/OpenGL.h>

class RenderHardwareInterface : public QObject
{
Q_OBJECT
public:
    explicit RenderHardwareInterface(QObject *parent = nullptr);
    int Init(Uint32 flags);

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

    /*SDL Events*/
    bool WindowShouldClose = false;
    void SDLEventHandle();
    void SDLRender();
    
    /*Performance*/
    void FrameRateLock();
    
signals:
    void on_error(int code, string error);

};

#endif // RHI_H

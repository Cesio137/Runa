#ifndef RENDERHARDWAREINTERFACE_H
#define RENDERHARDWAREINTERFACE_H

#include <QObject>
#include <QThread>
#include <RenderingSettings/RenderingEngineSettings.h>
#include <OpenGL/OpenGL.h>
#include <QPair>

class RenderHardwareInterface : public QObject
{
Q_OBJECT
public:
    explicit RenderHardwareInterface(QObject *parent = nullptr);
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
    void FrameRateLock();
    
signals:
    void on_error(int code, QByteArray error);

};

#endif // RHI_H

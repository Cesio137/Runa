#include "RenderHardwareInterface.h"

RenderHardwareInterface::RenderHardwareInterface(QObject *parent)
        : QObject{parent}
{
    
}

void RenderHardwareInterface::Initialize()
{
    OGL = new QOpenGL();
    QObject::connect(OGL, SIGNAL(PreInitialize(ImGuiIO&)), this, SLOT(QSlotPreInitialize(ImGuiIO&)));
    QObject::connect(OGL, SIGNAL(Ready()), this, SLOT(QSlotReady()));
    QObject::connect(OGL, SIGNAL(RenderInterface(float)), this, SLOT(QSlotRenderInterface(float)));
    QObject::connect(OGL, SIGNAL(Render(float)), this, SLOT(QSlotRender(float)));
    OGL->OGLInit();
}

void RenderHardwareInterface::PreInitialize(ImGuiIO& io)
{
}

void RenderHardwareInterface::Ready()
{
}

void RenderHardwareInterface::RenderInterface(float delta)
{
}

void RenderHardwareInterface::Render(float delta)
{
}

void RenderHardwareInterface::QSlotPreInitialize(ImGuiIO& io)
{
    PreInitialize(io);
}

void RenderHardwareInterface::QSlotReady()
{
    Ready();
}

void RenderHardwareInterface::QSlotRenderInterface(float delta)
{
    RenderInterface(delta);
}

void RenderHardwareInterface::QSlotRender(float delta)
{
    Render(delta);
}

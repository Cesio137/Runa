#include "RHI.h"

QRHI::QRHI(QObject *parent, int rhi)
    : QObject{parent}
{
    OGL = new QOpenGL();

#ifdef GRAPHICS_API_OPENGL
    connect(OGL, SIGNAL(Ready(ImGuiIO&)), this, SLOT(QReady(ImGuiIO&)));
    connect(OGL, SIGNAL(RenderInterface(float)), this, SLOT(QRenderInterface(float)));
    connect(OGL, SIGNAL(Tick(float)), this, SLOT(QTick(float)));
#endif
}

QRHI::~QRHI()
{
#ifdef GRAPHICS_API_OPENGL
    delete OGL;
#endif
}

void QRHI::Initialize()
{
#ifdef GRAPHICS_API_OPENGL
    OGL->Initialize();
#endif
}

void QRHI::WaitForEvent(bool wait)
{
    OGL->WaitForEvents = wait;
}

void QRHI::EnableVSync(bool SwapInterval)
{
#ifdef GRAPHICS_API_OPENGL
    SDL_GL_SetSwapInterval(SwapInterval);
#endif
}

void QRHI::SetMaxFrameRate(int FrameRate)
{
#ifdef GRAPHICS_API_OPENGL
    OGL->SetMaxFrameRate(FrameRate);
#endif
}

void QRHI::QReady(ImGuiIO& io)
{
    emit Ready(io);
}

void QRHI::QRenderInterface(float DeltaTime)
{
    emit RenderInterface(DeltaTime);
}

void QRHI::QTick(float DeltaTime)
{
    emit Tick(DeltaTime);
}



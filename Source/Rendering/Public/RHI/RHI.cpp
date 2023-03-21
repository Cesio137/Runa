#include "RHI.h"

QRHI::QRHI(QObject *parent, int rhi)
    : QObject{parent}
{
#define RHI_API rhi

    connect(this, SIGNAL(BeginPlay()), parent, SLOT(BeginPlay()));
    connect(this, SIGNAL(Tick(float)), parent, SLOT(Tick(float)));
    connect(this, SIGNAL(ConstructInterface()), parent, SLOT(ConstructInterface()));
    
    switch (RHI_API)
    {
    case 0:
        qogl = new QOpenGL(this);
        break;
    
    default:
        qogl = new QOpenGL(this);
        break;
    }
}

void QRHI::QBeginPlay()
{
    emit BeginPlay();
}

void QRHI::QTick(float DeltaTime)
{
    emit Tick(DeltaTime);
}

void QRHI::QConstructInterface()
{
    emit ConstructInterface();
}

bool QRHI::getGlfwWindow(GLFWwindow*& window)
{
    window = qogl->GetWindow();
    return window ? true : false;
}

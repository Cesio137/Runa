#include "RHI.h"

QRHI::QRHI(QObject *parent)
    : QObject{parent}
{
    connect(this, SIGNAL(BeginPlay()), parent, SLOT(BeginPlay()));
    connect(this, SIGNAL(Tick(float)), parent, SLOT(Tick(float)));
    QOpenGL* ogl = new QOpenGL(this);
}

void QRHI::QBeginPlay()
{
    emit BeginPlay();
}

void QRHI::QTick(float DeltaTime)
{
    emit Tick(DeltaTime);
}

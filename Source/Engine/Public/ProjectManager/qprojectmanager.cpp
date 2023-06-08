
#include "qprojectmanager.h"

QProjectManager::QProjectManager(QObject *parent)
    : QObject{parent}
{
    RHI = new QRHI(this);
    connect(RHI, SIGNAL(Ready(ImGuiIO&)), this, SLOT(QReady(ImGuiIO&)));
    connect(RHI, SIGNAL(RenderInterface(float)), this, SLOT(QRenderInterface(float)));
    connect(RHI, SIGNAL(Tick(float)), this, SLOT(QTick(float)));
    RHI->Initialize();
}

QProjectManager::~QProjectManager()
{
    delete IO;
}

void QProjectManager::QReady(ImGuiIO& io)
{
    IO = &io;
    RHI->WaitForEvent(false);
}

void QProjectManager::QRenderInterface(float DeltaTime)
{
    ImGui::Begin("test");
    ImGui::Text("delta time: %f", IO->DeltaTime);
    ImGui::End();
}

void QProjectManager::QTick(float DeltaTime)
{
    qDebug() << IO->DeltaTime;
}



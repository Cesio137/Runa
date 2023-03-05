#include "projectmanager.h"

QProjectManager::QProjectManager(QObject *parent)
        : QObject{parent}
{
    QRHI* RHI = new QRHI(this);
}

void QProjectManager::BeginPlay()
{

}

void QProjectManager::Tick(float DeltaTime)
{
    
}

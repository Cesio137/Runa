#include "engine.h"

QEngine::QEngine(QObject *parent)
    : QObject{parent}
{
    QRHI* rhi = new QRHI();
}

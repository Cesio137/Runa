#include "RHI.h"

QRHI::QRHI(QObject *parent)
    : QObject{parent}
{
    QOpenGL* ogl = new QOpenGL();
}

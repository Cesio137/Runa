#include "rhi.h"

QRHI::QRHI(QObject *parent)
    : QObject{parent}
{
    OGL* opengl = new OGL();
}

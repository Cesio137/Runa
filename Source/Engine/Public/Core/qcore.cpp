#include "qcore.h"

QCore::QCore(QObject *parent)
    : QObject{parent}
{
    ProjectManager = new QProjectManager();
}

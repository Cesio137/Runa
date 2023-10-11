#include "QCore.h"

QCore::QCore(int& argc, char** argv): QCoreApplication(argc, argv)
{
    if (argc <= 1)
    {
        qDebug() << argv[0];
    }
}

QCore::~QCore()
{
}

int QCore::exec()
{
    launcher = new Launcher();
    QObject::connect(launcher, SIGNAL(on_error(int, string)), this, SLOT(QSlotDebugError(int, string)));
    return exec_code;
}

void QCore::QSlotDebugError(int code, string error)
{
    exec_code = code;
    if (error != "")
    {
        qDebug() << error.c_str();
    }
}

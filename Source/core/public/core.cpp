#include "Core.h"

Core::Core(int& argc, char** argv): QCoreApplication(argc, argv)
{
    if (argc <= 1)
    {
        qDebug() << argv[0];
    }
}

Core::~Core()
{
}

int Core::exec()
{
    launcher = new Launcher();
    QObject::connect(launcher, SIGNAL(on_error(int, FString)), this, SLOT(QSlotDebugError(int, FString)));
    return exec_code;
}

void Core::QSlotDebugError(int code, FString error)
{
    exec_code = code;
    if (error != "")
    {
        qDebug() << error;
    }
}

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
    international = new InternationalComponent();
    launcher = new Launcher();
    QObject::connect(launcher, SIGNAL(on_error(int, QString)), this, SLOT(QSlotDebugError(int, QString)));
    return exec_code;
}

void Core::QSlotDebugError(int code, QString error)
{
    exec_code = code;
    if (error != "")
    {
        qDebug() << error;
    }
}

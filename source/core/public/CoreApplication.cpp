#include "CoreApplication.h"

CoreApplication::CoreApplication(int& argc, char** argv)
{
    if (argc <= 1)
    {
        qDebug() << argv[0];
    }

    
}

CoreApplication::~CoreApplication()
{
}

int CoreApplication::exec()
{
    international = new InternationalComponent(EN_US);
    launcher = new Launcher();
    QObject::connect(launcher, SIGNAL(on_error(int, QString)), this, SLOT(QSlotDebugError(int, QString)));
    return exec_code;
}

void CoreApplication::QSlotDebugError(int code, QString error)
{
    exec_code = code;
    if (error != "")
    {
        qDebug() << error;
    }
}

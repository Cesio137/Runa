#include "CoreApplication.h"

CoreApplication::CoreApplication(int& argc, char** argv, int i)
    : QCoreApplication(argc, argv, i)
{
    internationalComponent = new InternationalComponent(PT_BR);
}

CoreApplication::~CoreApplication()
{
    delete(launcher);
    delete(internationalComponent);
}

int CoreApplication::exec()
{
    launcher = new Launcher();
    return 0;
}

void CoreApplication::QSlotDebugError(int code, QByteArray error)
{

}

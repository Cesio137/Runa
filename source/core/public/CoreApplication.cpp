#include "CoreApplication.h"

CoreApplication::CoreApplication(int& argc, char** argv)
{

}

CoreApplication::~CoreApplication()
{

}

int CoreApplication::exec()
{
    launcher = new Launcher();
    return launcher->Init(0);
}

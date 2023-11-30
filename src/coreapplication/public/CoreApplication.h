#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <Launcher.h>

using namespace std;

class CoreApplication
{
public:
    CoreApplication(int& argc, char** argv);
    ~CoreApplication();

    int exec();

private:
    Launcher* launcher;
};

#endif // CORE_H

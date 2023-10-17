#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QCoreApplication>
#include <Types.h>
#include <Launcher.h>

using namespace std;

class Core : public QCoreApplication
{
    Q_OBJECT
public:
    Core(int& argc, char** argv);
    ~Core();

    int exec();

private:
    int exec_code = 0;
    Launcher* launcher = nullptr;



private slots:
    void QSlotDebugError(int code, FString error);

};

#endif // CORE_H

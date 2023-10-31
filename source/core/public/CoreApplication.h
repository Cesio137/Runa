#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <Launcher.h>
#include <InternationalComponent.h>

using namespace std;

class CoreApplication : public QObject
{
    Q_OBJECT
public:
    CoreApplication(int& argc, char** argv);
    ~CoreApplication();

    int exec();

private:
    int exec_code = 0;
    Launcher* launcher;
    InternationalComponent* international;



private slots:
    void QSlotDebugError(int code, QString error);

};

#endif // CORE_H

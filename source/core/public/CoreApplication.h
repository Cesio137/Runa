#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include <Launcher.h>
#include <InternationalComponent.h>

using namespace std;

class CoreApplication : public QCoreApplication
{
    Q_OBJECT
public:
    CoreApplication(int& argc, char** argv, int i = 0);
    ~CoreApplication();

    int exec();

private:
    int exec_code = 0;
    Launcher* launcher;
    InternationalComponent* internationalComponent;

private slots:
    void QSlotDebugError(int code, QByteArray error);

};

#endif // CORE_H

#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QCoreApplication>
#include <Launcher.h>
#include <InternationalComponent.h>

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
    InternationalComponent* international = nullptr;



private slots:
    void QSlotDebugError(int code, QString error);

};

#endif // CORE_H

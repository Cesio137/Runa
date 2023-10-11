#ifndef QCORE_H
#define QCORE_H

#include <QCoreApplication>
#include <launcher/Launcher.h>
using namespace std;

class QCore : public QCoreApplication
{
    Q_OBJECT
public:
    QCore(int& argc, char** argv);
    ~QCore();
    
    int exec();

private:
    int exec_code = 0;
    Launcher* launcher = nullptr;

private slots:
    void QSlotDebugError(int code, string error);

};

#endif // QCORE_H

/*
class QCore : public QObject
{
    Q_OBJECT
public:
    explicit QCore(QObject *parent = nullptr);

signals:

};
*/

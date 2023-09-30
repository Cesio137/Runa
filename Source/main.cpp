#include <QCoreApplication>
#include <launcher/Launcher.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Launcher* L = new Launcher();

    return a.exec();
}

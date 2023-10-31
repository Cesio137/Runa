#include <QCoreApplication>
#include <CoreApplication.h>

int main(int argc, char *argv[])
{
    CoreApplication a(argc, argv);
    
    return a.exec();;
}

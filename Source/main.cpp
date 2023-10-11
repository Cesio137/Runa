#include <QCoreApplication>
#include <core/QCore.h>

int main(int argc, char *argv[])
{
    QCore Core(argc, argv);
    
    return Core.exec();
}

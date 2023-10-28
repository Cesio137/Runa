#include <QCoreApplication>
#include <Core.h>

int main(int argc, char *argv[])
{
    Core a(argc, argv);
    
    return a.exec();;
}

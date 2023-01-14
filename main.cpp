#include <QCoreApplication>
#include <QDebug>
#include "engine/engine.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    qDebug() << "Hello World";
    Engine* engine = new Engine();
    return QCoreApplication::exec();
}

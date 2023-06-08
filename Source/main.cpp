#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <Core/qcore.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Lumen_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    //QProjectManager* rhi = new QProjectManager();
    QCore *core = new QCore();
    return a.exec();
}

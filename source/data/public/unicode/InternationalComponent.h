#ifndef INTERNATIONALCOMPONENT_H
#define INTERNATIONALCOMPONENT_H

#include <QObject>
#include <QLocale>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <Config.h>
#include <EUnicode.h>

using namespace std;

class InternationalComponent : public QObject
{
    Q_OBJECT
    friend class QText;
public:
    InternationalComponent(uint8_t id);
    ~InternationalComponent();
    static void SetAppLocaleID(uint8_t id);
    static uint8_t GetAppLocaleID();
    static QString toLocalStr(QString str);

private:
    static void SetEngineLocaleID(uint8_t id);
    static uint8_t GetEngineLocaleID();
    static void SetBaseAppLocaleID(uint8_t id);
    static uint8_t GetBaseAppLocaleID();
    static QString toEngineLocalStr(QString str);
    inline static QString JsonDocument;
    inline static QJsonDocument locale_doc;
    inline static QJsonObject message_obj;
    inline static uint8_t EngineLocale = ELanguageID::EN_US;
    inline static uint8_t BaseAppLocale = ELanguageID::EN_US;
    inline static uint8_t AppLocale = ELanguageID::EN_US;
    
};


#endif // INTERNATIONALCOMPONENT

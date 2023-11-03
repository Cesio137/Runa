#ifndef INTERNATIONALCOMPONENT_H
#define INTERNATIONALCOMPONENT_H

#include <QObject>
#include <QLocale>
#include <QFile>
#include <QTextStream>
#include <boost/json.hpp>
#include <Config.h>
#include <EUnicode.h>

using namespace std;
using namespace boost;

class InternationalComponent : public QObject
{
    Q_OBJECT
public:
    InternationalComponent(ELanguageID id);
    ~InternationalComponent();
    static void SetLocaleID(ELanguageID id);
    static ELanguageID GetLocaleID();
    static QString ParseStr(QString str);

private:
    inline static QString JsonText;
    inline static ELanguageID language = ELanguageID::EN_US;
    
};


#endif // INTERNATIONALCOMPONENT

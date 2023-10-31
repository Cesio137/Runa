#ifndef INTERNATIONALCOMPONENT_H
#define INTERNATIONALCOMPONENT_H

#include <QObject>
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
   InternationalComponent(ELanguages Language = ELanguages::EEN_US);
  ~InternationalComponent();
  static bool ChangeLanguage();

private:
    inline static QString JsonText;
    inline static ELanguages language = ELanguages::EEN_US;
    
};


#endif // INTERNATIONALCOMPONENT

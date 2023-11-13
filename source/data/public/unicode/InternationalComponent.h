#ifndef INTERNATIONALCOMPONENT_H
#define INTERNATIONALCOMPONENT_H

#include <string>
#include <EUnicode.h>

using namespace std;

class InternationalComponent
{
    friend class FText;
public:
    InternationalComponent(uint8_t id);
    ~InternationalComponent();
    static void SetAppLocaleID(uint8_t id);
    static uint8_t GetAppLocaleID();
    static string toLocalStr(string str);

private:
    static void SetEngineLocaleID(uint8_t id);
    static uint8_t GetEngineLocaleID();
    static void SetBaseAppLocaleID(uint8_t id);
    static uint8_t GetBaseAppLocaleID();
    static string toEngineLocalStr(string str);
    inline static uint8_t EngineLocale = ELanguageID::EN_US;
    inline static uint8_t BaseAppLocale = ELanguageID::EN_US;
    inline static uint8_t AppLocale = ELanguageID::EN_US;

};

#endif // INTERNATIONALCOMPONENT

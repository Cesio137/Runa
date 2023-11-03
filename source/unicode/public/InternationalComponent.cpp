#include "InternationalComponent.h"

InternationalComponent::InternationalComponent(ELanguageID id)
{
#ifdef ENGINE_BUILD_DEBUG
    QFile UnicodeJson(DICTIONARY_PATH);
    if (!UnicodeJson.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream JsonStream(&UnicodeJson);
    JsonText = JsonStream.readAll();
    qDebug() << JsonText;
#endif   
    
}

InternationalComponent::~InternationalComponent()
{
}

void InternationalComponent::SetLocaleID(ELanguageID id)
{
    language = id;
}

ELanguageID InternationalComponent::GetLocaleID()
{
    return language;
}

QString InternationalComponent::ParseStr(QString str)
{
    
    return "";
}

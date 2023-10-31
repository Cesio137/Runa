#include "InternationalComponent.h"

InternationalComponent::InternationalComponent(ELanguages Language)
{
#ifdef ENGINE_BUILD_DEBUG
    QFile UnicodeJson(DICTIONARY_PATH);
    if (!UnicodeJson.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream JsonStream(&UnicodeJson);
    JsonText = JsonStream.readAll();
#endif
}

InternationalComponent::~InternationalComponent()
{
}

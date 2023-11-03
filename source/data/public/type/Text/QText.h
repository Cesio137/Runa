#ifndef FTEXT_H
#define FTEXT_H

#include <QLocale>
#include <QString>
#include <QMap>
#include "EUnicode.h"
#include "InternationalComponent.h"

using namespace std;

class QText
{
public:
    QText() { tr(); }
    QText(const QString& str) { Text.insert(ELanguageID::EN_US, str); tr(); }
    QText(const ELanguageID& locale, const QString& str) { Text.insert(locale, str); tr(); }
    QText(const string& str) { Text.insert(ELanguageID::EN_US, QString::fromStdString(str)); tr(); }
    QText(const ELanguageID& locale, const string& str) { Text.insert(locale, QString::fromStdString(str)); tr(); }
    QText(const char* str) { Text.insert(ELanguageID::EN_US, QString(str)); tr(); }
    QText(const ELanguageID& locale, const char* str) { Text.insert(locale, QString(str)); tr(); }
    
    //Set
    const void append(const QString& str) { Text.begin().value().append(str); tr(); }
    const void appendFromStdString(const string& str) { Text.begin().value().append(QString::fromStdString(str)); tr(); }
    const void appendFromUtf8(const char* str) { Text.begin().value().append(QString::fromUtf8(str)); tr(); }

    //Get
    const QString toCaseFolded() { return Text.contains(InternationalComponent::GetLocaleID()) ? Text[InternationalComponent::GetLocaleID()].toCaseFolded() : Text.begin().value(); }
    const string toStdString() { return Text.contains(InternationalComponent::GetLocaleID()) ? Text[InternationalComponent::GetLocaleID()].toStdString() : Text.begin().value().toStdString(); }
    const char* c_str()
    {
        // Temp QByteArray
        QByteArray temp_qbytearray( Text.contains(InternationalComponent::GetLocaleID()) ? Text[InternationalComponent::GetLocaleID()].toUtf8() : Text.begin().value().toUtf8());

        // Convert to const char*
        const char* const_char_ptr = temp_qbytearray.constData();

        // Returning pointer with data from QByteArray
        return const_char_ptr;
    }

    //Translation
    

private:
    QMap<ELanguageID, QString> Text;
    void tr()
    {
#ifdef ENGINE_BUILD_DEBUG
        if (Text.begin().key() == EN_US)
        {
            InternationalComponent::ParseStr(Text.begin().value());
        }
#endif
    }
};

#endif // FTEXT_H

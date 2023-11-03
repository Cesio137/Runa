#ifndef FTEXT_H
#define FTEXT_H

#include <QLocale>
#include <QString>
#include <QMap>
#include <InternationalComponent.h>

using namespace std;

class QText
{
public:
    QText() { tr(); }
    QText(const QString& str) : Text(QMap<uint8_t, QString>{ {EN_US, str} }) { tr(); }
    QText(const ELanguageID& localeID, const QString& str) : Text(QMap<uint8_t, QString>{ {localeID, str} }) { tr(); }
    QText(const string& str) : Text(QMap<uint8_t, QString>{ {EN_US, QString::fromStdString(str)} }) { tr(); }
    QText(const ELanguageID& localeID, const string& str) : Text(QMap<uint8_t, QString>{ {localeID, QString::fromStdString(str)} }) { tr(); }
    QText(const char* str) : Text(QMap<uint8_t, QString>{ {EN_US, QString::fromStdString(str)} }) { tr(); }
    QText(const ELanguageID& localeID, const char* str) : Text(QMap<uint8_t, QString>{ {localeID, QString::fromStdString(str)} }) { tr(); }
    
    //Set
    const void append(const QString& str) { Text.begin().value().append(str); tr(); }
    const void appendFromStdString(const string& str) { Text.begin().value().append(QString::fromStdString(str)); tr(); }
    const void appendFromUtf8(const char* str) { Text.begin().value().append(QString::fromUtf8(str)); tr(); }

    //Get
    const QString toCaseFolded() { return Text.contains(InternationalComponent::GetLocaleID()) ? Text[InternationalComponent::GetLocaleID()].toCaseFolded() : Text.begin().value(); }
    const string toStdString() { return Text.contains(InternationalComponent::GetLocaleID()) ? Text[InternationalComponent::GetLocaleID()].toStdString() : Text.begin().value().toStdString(); }
    const QByteArray c_str()
    {
        // Temp QByteArray
        QByteArray temp_qbytearray = Text.contains(InternationalComponent::GetLocaleID()) ? Text[InternationalComponent::GetLocaleID()].toUtf8() : Text.begin().value().toUtf8();
        
        return temp_qbytearray.constData();
    }

    //Translation
    

private:
    QMap<uint8_t, QString> Text;
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

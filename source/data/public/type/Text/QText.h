#ifndef QTEXT_H
#define QTEXT_H

#include <QLocale>
#include <QString>
#include <QMap>
#include <InternationalComponent.h>
#include <Config.h>

using namespace std;

class QText
{
    friend class Launcher;
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
    const QString toCaseFolded()
    {
        //return Text.contains(InternationalComponent::GetLocaleID()) ? Text[InternationalComponent::GetLocaleID()].toCaseFolded() : Text.begin().value();
        return "";
    }
    const string toStdString()
    {
        //return Text.contains(InternationalComponent::GetLocaleID()) ? Text[InternationalComponent::GetLocaleID()].toStdString() : Text.begin().value().toStdString();
        return "";
    }
    const QByteArray c_str()
    {
        // Temp QByteArray
        QByteArray temp_qbytearray;
        temp_qbytearray = Text.contains(InternationalComponent::GetEngineLocaleID()) ? Text[InternationalComponent::GetEngineLocaleID()].toUtf8() : Text.begin().value().toUtf8();

        return temp_qbytearray;
    }

    //Translation
    

private:
    QText(const uint8_t& use_private) { translate(); }
    QText(const uint8_t& use_private, const QString& str) : Text(QMap<uint8_t, QString>{ {EN_US, str} }) { translate(); }
    QText(const uint8_t& use_private, const ELanguageID& localeID, const QString& str) : Text(QMap<uint8_t, QString>{ {localeID, str} }) { translate(); }
    QText(const uint8_t& use_private, const string& str) : Text(QMap<uint8_t, QString>{ {EN_US, QString::fromStdString(str)} }) { translate(); }
    QText(const uint8_t& use_private, const ELanguageID& localeID, const string& str) : Text(QMap<uint8_t, QString>{ {localeID, QString::fromStdString(str)} }) { translate(); }
    QText(const uint8_t& use_private, const char* str) : Text(QMap<uint8_t, QString>{ {EN_US, QString::fromStdString(str)} }) { translate(); }
    QText(const uint8_t& use_private, const ELanguageID& localeID, const char* str) : Text(QMap<uint8_t, QString>{ {localeID, QString::fromStdString(str)} }) { translate(); }

    QMap<uint8_t, QString> Text;
    QByteArray toByteArray()
    {
        // Temp QByteArray
        QByteArray temp_qbytearray = Text.contains(InternationalComponent::GetEngineLocaleID()) ? Text[InternationalComponent::GetEngineLocaleID()].toUtf8() : Text.begin().value().toUtf8();
        if (temp_qbytearray.isNull() || temp_qbytearray.isEmpty())
            return "Error";
        return temp_qbytearray;
    }
    void translate()
    {
        if (InternationalComponent::EngineLocale == EN_US)
            return;

        QString msgtext;
        msgtext = InternationalComponent::toEngineLocalStr(Text.first());
        if (msgtext.isNull() || msgtext.isEmpty())
        {
            for (int i = 1; i < Text.size(); i++)
            {
                Text.remove(i);
            }
            return;
        }
        Text.insert(InternationalComponent::GetEngineLocaleID(), msgtext);
    }
    void tr()
    {
        QString msgtext;
        msgtext = InternationalComponent::toEngineLocalStr(Text.first());
        if (msgtext.isNull())
        {

            return;
        }
        Text.insert(ELanguageID::PT_BR, msgtext);
    }
};

#endif // QTEXT_H

#include "InternationalComponent.h"


InternationalComponent::InternationalComponent(uint8_t id)
{
    EngineLocale = id;
    QFile UnicodeJson(DICTIONARY_PATH);
    if (UnicodeJson.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream JsonStream(&UnicodeJson);
        JsonDocument = JsonStream.readAll();
        locale_doc = QJsonDocument::fromJson(JsonDocument.toUtf8());
        UnicodeJson.close();
        QJsonObject root = locale_doc.object();
        // Acess "messages"
        QJsonValue messagesValue = root.value("messages");
        if (!messagesValue.isObject())
            return;

        message_obj = messagesValue.toObject();
    }
}

InternationalComponent::~InternationalComponent()
{
    if (locale_doc.isNull() || locale_doc.isEmpty())
        return;

    QFile UnicodeJson(DICTIONARY_PATH);
    if (UnicodeJson.open(QIODevice::WriteOnly) )
    {
        QTextStream out(&UnicodeJson);
        JsonDocument = locale_doc.toJson();
        qDebug() << JsonDocument;
        out << JsonDocument;
        UnicodeJson.close();
    }
}

void InternationalComponent::SetEngineLocaleID(uint8_t id)
{
    EngineLocale = id;
}

uint8_t InternationalComponent::GetEngineLocaleID()
{
    return EngineLocale;
}

void InternationalComponent::SetBaseAppLocaleID(uint8_t id)
{
    BaseAppLocale = id;
}

uint8_t InternationalComponent::GetBaseAppLocaleID()
{
    return BaseAppLocale;
}

void InternationalComponent::SetAppLocaleID(uint8_t id)
{
    AppLocale = id;
}

uint8_t InternationalComponent::GetAppLocaleID()
{
    return AppLocale;
}

QString InternationalComponent::toLocalStr(QString str)
{

    return "";
}

QString InternationalComponent::toEngineLocalStr(QString str)
{
    if (message_obj.isEmpty())
        return nullptr;
    QString msgtext;

    QJsonValue keyValue = message_obj.value(str);
    if (!keyValue.isObject())
    {
#ifdef ENGINE_BUILD_DEBUG
        QJsonObject msg_obj;
        for (int i = 1; i < 9; ++i)
        {
            switch (EngineLocale)
            {
                case PT_BR:
                    msg_obj.insert("pt_BR", "");
                    break;
                case ES:
                    msg_obj.insert("es", "");
                    break;
                case FR:
                    msg_obj.insert("fr", "");
                    break;
                case DE:
                    msg_obj.insert("de", "");
                    break;
                case IT:
                    msg_obj.insert("it", "");
                    break;
                case RU:
                    msg_obj.insert("ru", "");
                    break;
                case ZH_CN:
                    msg_obj.insert("zh_CH", "");
                    break;
                case JA:
                    msg_obj.insert("ja", "");
                    break;
                case KO_KR:
                    msg_obj.insert("ko_KR", "");
                    break;
            }
        }

        message_obj.insert(str, msg_obj);
        locale_doc.object().value("messages").toObject().insert(str, msg_obj);
#endif
        return nullptr;
    }

    QJsonObject keyObject = keyValue.toObject();
    QJsonValue localeValue;
    switch (EngineLocale)
    {
        case PT_BR:
            localeValue = keyObject.value("pt_BR");
            break;
        case ES:
            localeValue = keyObject.value("es");
            break;
        case FR:
            localeValue = keyObject.value("fr");
            break;
        case DE:
            localeValue = keyObject.value("de");
            break;
        case IT:
            localeValue = keyObject.value("it");
            break;
        case RU:
            localeValue = keyObject.value("ru");
            break;
        case ZH_CN:
            localeValue = keyObject.value("zh_CH");
            break;
        case JA:
            localeValue = keyObject.value("ja");
            break;
        case KO_KR:
            localeValue = keyObject.value("ko_KR");
            break;
    }
    if (!localeValue.isString())
        return nullptr;

    msgtext = localeValue.toString();

    return msgtext;
}





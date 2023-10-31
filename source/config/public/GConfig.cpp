#include "GConfig.h"

GConfig::GConfig(const QString& organization, const QString& application, QObject* parent)
    : QSettings(organization, application, parent)
{
}

GConfig::GConfig(Scope scope, const QString& organization, const QString& application, QObject* parent)
    : QSettings(scope, organization, application, parent)
{
}

GConfig::GConfig(Format format, Scope scope, const QString& organization, const QString& application, QObject* parent)
    : QSettings(format, scope, organization, application, parent)
{
}

GConfig::GConfig(const QString& fileName, Format format, QObject* parent)
    : QSettings(fileName, format, parent)
{
}

GConfig::GConfig(QObject* parent)
    : QSettings(parent)
{
}

GConfig::GConfig(Scope scope, QObject* parent)
    : QSettings(scope, parent)
{
}

#ifndef GCONFIG_H
#define GCONFIG_H

#include <QSettings>

class GConfig : public QSettings
{
public:
    GConfig(const QString& organization, const QString& application, QObject* parent);
    GConfig(Scope scope, const QString& organization, const QString& application, QObject* parent);
    GConfig(Format format, Scope scope, const QString& organization, const QString& application, QObject* parent);
    GConfig(const QString& fileName, Format format, QObject* parent);
    explicit GConfig(QObject* parent = nullptr);
    GConfig(Scope scope, QObject* parent);

private:
    Q_OBJECT

public:

signals:

};

#endif // GCONFIG_H

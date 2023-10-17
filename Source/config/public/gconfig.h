#ifndef GCONFIG_H
#define GCONFIG_H

#include <QObject>

class GConfig : public QObject
{
    Q_OBJECT
public:
    explicit GConfig(QObject *parent = nullptr);

signals:

};

#endif // GCONFIG_H

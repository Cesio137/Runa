#ifndef QENGINE_H
#define QENGINE_H

#include <QObject>
#include <QDebug>
#include "Backend/rhi.h"

using namespace std;

class QEngine : public QObject
{
    Q_OBJECT
public:
    QEngine(QObject *parent);

signals:

private:

};

#endif // QENGINE_H

#ifndef QRHI_H
#define QRHI_H

#include <QObject>
#include <Backend/ogl.h>

class QRHI : public QObject
{
    Q_OBJECT
public:
    explicit QRHI(QObject *parent = nullptr);

signals:

};

#endif // QRHI_H

#ifndef QRHI_H
#define QRHI_H

#include <QObject>
#include <OpenGL/qopengl.h>

class QRHI : public QObject
{
    Q_OBJECT
public:
    explicit QRHI(QObject *parent = nullptr);

public slots:
    void QBeginPlay();
    void QTick(float DeltaTime);

signals:
    void BeginPlay();
    void Tick(float DeltaTime);

};

#endif // QRHI_H


#ifndef QPROJECTMANAGER_H
#define QPROJECTMANAGER_H


#include <QObject>
#include <RHI/RHI.h>


class QProjectManager : public QObject
{
    Q_OBJECT
public:
    explicit QProjectManager(QObject *parent = nullptr);
    ~QProjectManager();

public slots:
    void QReady(ImGuiIO& io);
    void QRenderInterface(float DeltaTime);
    void QTick(float DeltaTime);
    

private:
    ImGuiIO *IO;
    QRHI* RHI = nullptr;

};

#endif // QPROJECTMANAGER_H

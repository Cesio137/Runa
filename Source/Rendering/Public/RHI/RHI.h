#ifndef QRHI_H
#define QRHI_H

#include <QObject>
#include <OpenGL/qopengl.h>

class QRHI : public QObject
{
Q_OBJECT
public:
    explicit QRHI(QObject *parent = nullptr, int rhi = 0);
    ~QRHI();
    void Initialize();

    //Event
    void WaitForEvent(bool wait);

    //FrameRate
    void EnableVSync(bool SwapInterval);
    void SetMaxFrameRate(int FrameRate);

public slots:
    void QReady(ImGuiIO& io);
    void QRenderInterface(float DeltaTime);
    void QTick(float DeltaTime);

private:
    QOpenGL* OGL = nullptr;

signals:
    void Ready(ImGuiIO& io);
    void RenderInterface(float DeltaTime);
    void Tick(float DeltaTime);

};
#endif // QRHI_H

#ifndef QRHI_H
#define QRHI_H

#include <QObject>
#include <OpenGL/qopengl.h>

#define RHI_API 0

class QRHI : public QObject
{
    Q_OBJECT
public:
    explicit QRHI(QObject *parent = nullptr, int rhi = 0);

public slots:
    void QBeginPlay();
    void QTick(float DeltaTime);
    void QConstructInterface();
    bool getGlfwWindow(GLFWwindow* &window);

private:
    QOpenGL* qogl;
    

signals:
    void BeginPlay();
    void Tick(float DeltaTime);
    void ConstructInterface();

};

#endif // QRHI_H

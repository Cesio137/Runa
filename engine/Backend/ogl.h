#ifndef OGL_H
#define OGL_H

#include <QObject>
#include <QDebug>
#include <QElapsedTimer>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MIN_OPENGL_MAJOR_VERSION 3
#define MIN_OPENGL_MINOR_VERSION 3

class OGL : public QObject
{
    Q_OBJECT
public:
    explicit OGL(QObject *parent = nullptr);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public slots:
    virtual void BeginPlay();
    virtual void Tick(const float DeltaTime);

signals:

private:
    bool InitOpenGL();
    GLFWwindow* window;
    QElapsedTimer timer;
};

#endif // OGL_H

#ifndef QOPENGL_H
#define QOPENGL_H

#include <QObject>
#include <QDebug>
#include <QElapsedTimer>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifndef OPENGL_MAJOR_MIN
#define OPENGL_MAJOR_MIN 3
#endif
#ifndef OPENGL_MINOR_MIN
#define OPENGL_MINOR_MIN 3
#endif

class QOpenGL : public QObject
{
    Q_OBJECT
public:
    explicit QOpenGL(QObject *parent = nullptr);

signals:
    void BeginPlay();
    void Tick(float DeltaTime);

private:
    GLFWwindow* window;
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void error_callback(int error, const char* description);
    QElapsedTimer deltaTime;
    
};

#endif // QOPENGL_H

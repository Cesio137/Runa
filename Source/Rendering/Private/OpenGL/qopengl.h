#ifndef QOPENGL_H
#define QOPENGL_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QElapsedTimer>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#ifndef OPENGL_MAJOR_MIN
	#define OPENGL_MAJOR_MIN 3
#endif
#ifndef OPENGL_MINOR_MIN
	#define OPENGL_MINOR_MIN 3
#endif

#ifndef MAX_FRAME_RATE
	#define MAX_FRAME_RATE 30
#endif

class QOpenGL : public QObject
{
    Q_OBJECT
public:
    explicit QOpenGL(QObject *parent = nullptr);
    void SetWindowTitle(QString title);
    GLFWwindow* GetWindow();

private:
    GLFWwindow* window;
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void error_callback(int error, const char* description);
    QElapsedTimer deltaTime;

    void FrameRate_Lock();

signals:
    void BeginPlay();
    void Tick(float DeltaTimne);
    void ConstructInterface();
    
};

#endif // QOPENGL_H

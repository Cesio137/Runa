#ifndef QOPENGL_H
#define QOPENGL_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QElapsedTimer>
#include <glad/glad.h>
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#ifndef OPENGL_MAJOR_VERSION
#define OPENGL_MAJOR_VERSION 3
#endif
#ifndef OPENGL_MINOR_VERSION
#define OPENGL_MINOR_VERSION 3
#endif

#ifndef GRAPHICS_API_OPENGL
#define GRAPHICS_API_OPENGL
#endif

class QOpenGL : public QObject
{
Q_OBJECT
public:
    explicit QOpenGL(QObject *parent = nullptr);
    ~QOpenGL();
    void Initialize();

    /* Variables */
    /* Events */
    bool WaitForEvents = true;
    /* Display */
    void SetMaxFrameRate(int framerate);

    /* Imgui */
    ImGuiIO &GetIO();

private:
    /* Variables */
    /* Static Reference */
    static QOpenGL* opengl;

    /* OpenGL Window */
    bool WindowShouldClose = false;
    QPair<int, int> OpenGL_Version;
    SDL_Renderer* Renderer;
    SDL_GLContext Context;
    SDL_Window* Window;
    QPair<int, int> viewportSize;

    /* Imgui */
    ImGuiIO *IO;
    QString glsl_Version;

    /* Performance */
    int MaxFrameRate;
    QElapsedTimer Time;

    /* Functions */
    /* Events */
    void EventHandle();
    static int WindowEventWatcher(void* data, SDL_Event* event);
    void Render();

    /* Performance */
    void FrameRateLock();

signals:
    void Ready(ImGuiIO& io);
    void RenderInterface(float DeltaTime);
    void Tick(float DeltaTime);
};

#endif // QOPENGL_H

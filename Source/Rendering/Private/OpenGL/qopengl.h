#ifndef QOPENGL_H
#define QOPENGL_H

#include <QObject>
#include <QThread>
#include <QPair>
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
    void OGLInit();

    void SetFrameRateLimit(int MaxFPS);
    int GetFrameRateLimit();
    
private:
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

    /* Events */
    void SDLEventHandle();
    void OGLRender();

    /* Performance */
    void FrameRateLock();

signals:
    void PreInitialize(ImGuiIO& io);
    void Ready();
    void RenderInterface(float DeltaTime);
    void Render(float DeltaTime);

};

#endif // QOPENGL_H

//
// Created by natha on 10/10/2023.
//

#ifndef NANOMETRO_OPENGL_H
#define NANOMETRO_OPENGL_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <Config.h>
#include <glad/glad.h>
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <RenderingSettings/RenderingUserSettings.h>
#include <RenderingConfig/RenderingConfig.h>

using namespace std;

struct FPair {int first; int second;};

class SDL_OpenGL {
public:
    explicit SDL_OpenGL();
    ~SDL_OpenGL();
    int SDL_OpenGL_Init();
    void SDL2_ImGui_Init();
    void SDL2_Destroy_OpenGL();
    int GetErrorCode(QString &log);

    static SDL_Window* GetWindow();

private:
    /* OpenGL Window */
    bool WindowShouldClose = false;
    FPair OpenGL_Version;
    SDL_Renderer* Renderer = nullptr;
    SDL_GLContext Context = nullptr;
    inline static SDL_Window* Window = nullptr;

    /* Imgui */
    QString glsl_Version;

    /* error */
    QString error_log;
    int error_code = 0;
};



#endif //NANOMETRO_OPENGL_H

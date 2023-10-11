#include "QUserSettings.h"

QUserSettings::QUserSettings(QObject *parent)
    : QObject{parent}
{

}

Uint32 QUserSettings::GetFullscreenMode(int value)
{
    return SDL_GetWindowFlags(SDL_OpenGL::GetWindow());
}

void QUserSettings::SetVSyncMode(int value)
{
    value = qBound(-1, value, 1);
    SDL_GL_SetSwapInterval(value);
}

int QUserSettings::GetVSyncMode()
{
    return SDL_GL_GetSwapInterval();
}

void QUserSettings::SetMaxFPS(int value)
{
    max_fps_ = value;
}

int QUserSettings::GetMaxFPS()
{
    return max_fps_;
}

#include "RenderingUserSettings.h"

RenderingUserSettings::RenderingUserSettings(QObject *parent)
    : QObject{parent}
{

}

void RenderingUserSettings::SetVSyncMode(int value)
{
    value = qBound(-1, value, 1);
    SDL_GL_SetSwapInterval(value);
}

int RenderingUserSettings::GetVSyncMode()
{
    return SDL_GL_GetSwapInterval();
}

void RenderingUserSettings::SetMaxFPS(Uint8 value)
{
    max_fps_ = value;
}

int RenderingUserSettings::GetMaxFPS()
{
    return max_fps_;
}

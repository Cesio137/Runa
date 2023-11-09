//
// Created by natha on 09/11/2023.
//

#include "RenderUserSettings.h"

void RenderUserSettings::SetVSyncMode(bool value, bool useAdaptative)
{
    if (value && useAdaptative)
    {
        SDL_GL_SetSwapInterval(-1);
        return;
    }

    SDL_GL_SetSwapInterval(value ? 1 : 0);
}

int RenderUserSettings::GetVSyncMode()
{
    return SDL_GL_GetSwapInterval();;
}

void RenderUserSettings::SetMaxFPS(int value)
{
    max_fps_ = value;
}

int RenderUserSettings::GetMaxFPS()
{
    return max_fps_;
}

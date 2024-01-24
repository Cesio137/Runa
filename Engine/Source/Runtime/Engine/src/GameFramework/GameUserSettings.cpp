//
// Created by natha on 26/11/2023.
//

#include "GameFramework/GameUserSettings.h"
#include <Container/String.h>
#include <System/Path.h>
#include <algorithm>
#include <SDL.h>

using namespace std;
using namespace Nanometro;

GameUserSettings::GameUserSettings()
{
    ImGui::GetIO().Fonts->AddFontDefault();

    String ContextMenuFontPath = SDL_GetBasePath();
    ContextMenuFontPath.append(Path::nativeSeparator("Engine/Misc/Fonts/Fira_Code/ttf/FiraCode-SemiBold.ttf"));
    ContextMenuFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(ContextMenuFontPath.c_str(), ContextMenuFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(ContextMenuFont != NULL);

    String DefaultFontPath = SDL_GetBasePath();
    DefaultFontPath.append(Path::nativeSeparator("Engine/Misc/Fonts/Fira_Code/ttf/FiraCode-Medium.ttf"));
    DefaultFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), DefaultFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(DefaultFont != NULL);
}

GameUserSettings::~GameUserSettings()
{
    
}

void GameUserSettings::SetUpdateEventMode(uint8_t EventMode)
{
    UpdateEventMode = EventMode;
}

uint8_t GameUserSettings::GetUpdateEventMode()
{
    return  UpdateEventMode;
}

void GameUserSettings::SetVSyncMode(uint8_t VSyncMode)
{
    int SwapMode = VSyncMode;
    SwapMode = clamp(SwapMode, 0 , 2);
    if (VSyncMode == SwapMode)
    {
        int isSupported = SDL_GL_SetSwapInterval(-1);
        if (isSupported < 0)
            SDL_GL_SetSwapInterval(1);
        return;
    }
    SDL_GL_SetSwapInterval(VSyncMode);
}

int GameUserSettings::GetVSyncMode()
{
    return SDL_GL_GetSwapInterval();
}

void GameUserSettings::SetFrameRateLimit(int NewLimit)
{
    FrameRateLimit = NewLimit;
}

int GameUserSettings::GetFrameRateLimit()
{
    return FrameRateLimit;
}

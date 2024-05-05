#include "GameFramework/GameUserSettings.h"
#include <System/Path.h>
#include <algorithm>
#include <SDL.h>

Nanometro::GameUserSettings::GameUserSettings()
{
    ImGui::GetIO().Fonts->AddFontDefault();

    std::string ContextMenuFontPath = SDL_GetBasePath();
    ContextMenuFontPath.append(Path::nativeSeparator("Engine/Misc/Fonts/Fira_Code/ttf/FiraCode-SemiBold.ttf"));
    ContextMenuFont = std::shared_ptr<ImFont>( ImGui::GetIO().Fonts->AddFontFromFileTTF(ContextMenuFontPath.c_str(), ContextMenuFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese()) );
    IM_ASSERT(ContextMenuFont != NULL);

    std::string DefaultFontPath = SDL_GetBasePath();
    DefaultFontPath.append(Path::nativeSeparator("Engine/Misc/Fonts/Fira_Code/ttf/FiraCode-Medium.ttf"));
    DefaultFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), DefaultFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(DefaultFont != NULL);
}

Nanometro::GameUserSettings::~GameUserSettings()
{
    delete ContextMenuFont;
    delete DefaultFont;
}

void Nanometro::GameUserSettings::SetUpdateEventMode(uint8_t EventMode)
{
    UpdateEventMode = EventMode;
}

uint8_t Nanometro::GameUserSettings::GetUpdateEventMode()
{
    return  UpdateEventMode;
}

void Nanometro::GameUserSettings::SetVSyncMode(uint8_t VSyncMode)
{
    int SwapMode = VSyncMode;
    SwapMode = std::clamp(SwapMode, 0 , 2);
    if (VSyncMode == SwapMode)
    {
        int isSupported = SDL_GL_SetSwapInterval(-1);
        if (isSupported < 0)
            SDL_GL_SetSwapInterval(1);
        return;
    }
    SDL_GL_SetSwapInterval(VSyncMode);
}

int Nanometro::GameUserSettings::GetVSyncMode()
{
    return SDL_GL_GetSwapInterval();
}

void Nanometro::GameUserSettings::SetFrameRateLimit(int NewLimit)
{
    FrameRateLimit = NewLimit;
}

int Nanometro::GameUserSettings::GetFrameRateLimit()
{
    return FrameRateLimit;
}

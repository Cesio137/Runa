//
// Created by natha on 09/11/2023.
//

#include "RenderEngineSettings.h"

int RenderEngineSettings::LoadSettings()
{
    ImGui::GetIO().Fonts->AddFontDefault();

    string ContextMenuFontPath = SDL_GetBasePath();
#ifdef HOST_SYSTEM_WINDOWS
    ContextMenuFontPath.append("assets\\Fonts\\Fira_Code\\ttf\\FiraCode-SemiBold.ttf");
#endif
#ifdef HOST_SYSTEM_LINUX
    ContextMenuFontPath.append("assets/Fonts/Fira_Code/ttf/FiraCode-SemiBold.ttf");
#endif
    ContextMenuFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(ContextMenuFontPath.c_str(), ContextMenuFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(ContextMenuFont != NULL);

    string DefaultFontPath = SDL_GetBasePath();
#ifdef HOST_SYSTEM_WINDOWS
    DefaultFontPath.append("assets\\Fonts\\Fira_Code\\ttf\\FiraCode-Medium.ttf");
#endif
#ifdef HOST_SYSTEM_LINUX
    DefaultFontPath.append("assets/Fonts/Fira_Code/ttf/FiraCode-Medium.ttf");
#endif
    DefaultFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), DefaultFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(DefaultFont != NULL);

    return 0;
}

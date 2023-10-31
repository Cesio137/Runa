#include "RenderingEngineSettings.h"

RenderingEngineSettings::RenderingEngineSettings(QObject *parent)
    : QObject{parent}
{

}

int RenderingEngineSettings::LoadSettings()
{
    ImGui::GetIO().Fonts->AddFontDefault();

    QString ContextMenuFontPath = SDL_GetBasePath();
#ifdef HOST_SYSTEM_WINDOWS
    ContextMenuFontPath.append("assets\\Fonts\\Fira_Code\\ttf\\FiraCode-SemiBold.ttf");
#endif
#ifdef HOST_SYSTEM_LINUX
    ContextMenuFontPath.append("assets/Fonts/Fira_Code/ttf/FiraCode-SemiBold.ttf");
#endif
    ContextMenuFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(ContextMenuFontPath.toUtf8(), ContextMenuFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(ContextMenuFont != NULL);

    QString DefaultFontPath = SDL_GetBasePath();
#ifdef HOST_SYSTEM_WINDOWS
    DefaultFontPath.append("assets\\Fonts\\Fira_Code\\ttf\\FiraCode-Medium.ttf");
#endif
#ifdef HOST_SYSTEM_LINUX
    DefaultFontPath.append("assets/Fonts/Fira_Code/ttf/FiraCode-Medium.ttf");
#endif
    DefaultFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(DefaultFontPath.toUtf8(), DefaultFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(DefaultFont != NULL);



    return 0;
}

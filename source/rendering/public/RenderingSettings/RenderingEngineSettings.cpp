#include "renderingenginesettings.h"

RenderingEngineSettings::RenderingEngineSettings(QObject *parent)
    : QObject{parent}
{

}

int RenderingEngineSettings::LoadSettings()
{
    ImGui::GetIO().Fonts->AddFontDefault();

    string ContextMenuFontPath = SDL_GetBasePath();
    ContextMenuFontPath.append("assets\\Fonts\\Fira_Code\\ttf\\FiraCode-SemiBold.ttf");
    ContextMenuFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(ContextMenuFontPath.c_str(), ContextMenuFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(ContextMenuFont != NULL);

    string DefaultFontPath = SDL_GetBasePath();
    DefaultFontPath.append("assets\\Fonts\\Fira_Code\\ttf\\FiraCode-Medium.ttf");
    DefaultFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), DefaultFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(DefaultFont != NULL);

    return 0;
}

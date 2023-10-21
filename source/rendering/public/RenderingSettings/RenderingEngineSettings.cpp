#include "renderingenginesettings.h"

RenderingEngineSettings::RenderingEngineSettings(QObject *parent)
    : QObject{parent}
{

}

int RenderingEngineSettings::LoadSettings()
{
    ImGui::GetIO().Fonts->AddFontDefault();

    QString ContextMenuFontPath = SDL_GetBasePath();
    ContextMenuFontPath.append("assets\\Fonts\\Fira_Code\\ttf\\FiraCode-SemiBold.ttf");
    ContextMenuFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(ContextMenuFontPath.toUtf8(), ContextMenuFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(ContextMenuFont != NULL);

    QString DefaultFontPath = SDL_GetBasePath();
    DefaultFontPath.append("assets\\Fonts\\Fira_Code\\ttf\\FiraCode-Medium.ttf");
    DefaultFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(DefaultFontPath.toUtf8(), DefaultFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(DefaultFont != NULL);

    return 0;
}

#include "RenderingEngineSettings.h"

RenderingEngineSettings::RenderingEngineSettings(QObject *parent)
    : QObject{parent}
{

}

int RenderingEngineSettings::LoadSettings()
{
    ImGui::GetIO().Fonts->AddFontDefault();

    QByteArray ContextMenuFontPath = SDL_GetBasePath();
    ContextMenuFontPath.append(QDir::toNativeSeparators("assets/Fonts/Fira_Code/ttf/FiraCode-SemiBold.ttf").toUtf8());
    ContextMenuFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(ContextMenuFontPath, ContextMenuFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(ContextMenuFont != NULL);

    QString DefaultFontPath = SDL_GetBasePath();
    DefaultFontPath.append(QDir::toNativeSeparators("assets/Fonts/Fira_Code/ttf/FiraCode-Medium.ttf"));
    DefaultFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(DefaultFontPath.toUtf8(), DefaultFontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(DefaultFont != NULL);

    return 0;
}

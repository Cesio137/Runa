//
// Created by Nathan on 09/11/2023.
//

#ifndef NANOMETRO_RENDERENGINESETTINGS_H
#define NANOMETRO_RENDERENGINESETTINGS_H

#include <string>
#include <SDL.h>
#include <imgui.h>
#include <Config.h>

using namespace std;

class RenderEngineSettings
{
public:
    static int LoadSettings();

    inline static ImFont* ContextMenuFont;
    inline static float ContextMenuFontSize = 14.0f;

    inline static ImFont* DefaultFont;
    inline static float DefaultFontSize = 16.0f;
};


#endif //NANOMETRO_RENDERENGINESETTINGS_H

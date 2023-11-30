//
// Created by natha on 26/11/2023.
//

#ifndef NANOMETRO_GAMEUSERSETTINGS_H
#define NANOMETRO_GAMEUSERSETTINGS_H

#include <cstdint>
#include <imgui.h>

class GameUserSettings
{
public:
    GameUserSettings();
    ~GameUserSettings();

    ImFont* ContextMenuFont;
    float ContextMenuFontSize = 14.0f;

    ImFont* DefaultFont;
    float DefaultFontSize = 16.0f;

    static void SetUpdateEventMode(uint8_t EventMode);
    static uint8_t GetUpdateEventMode();

    static void SetVSyncMode(uint8_t VSyncMode);
    static int GetVSyncMode();

    static void SetFrameRateLimit(int NewLimit);
    static int GetFrameRateLimit();

private:

protected:
    static inline int FrameRateLimit = 0;
    static inline uint8_t UpdateEventMode = 0;
};


#endif //NANOMETRO_GAMEUSERSETTINGS_H

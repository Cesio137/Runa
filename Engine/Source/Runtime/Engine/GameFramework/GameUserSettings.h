#pragma once

#include <cstdint>
#include <imgui.h>

namespace Nanometro
{
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

    protected:
        static inline int FrameRateLimit = 0;
        static inline uint8_t UpdateEventMode = 0;
    };
}

//
// Created by Nathan on 09/11/2023.
//

#ifndef NANOMETRO_RENDERUSERSETTINGS_H
#define NANOMETRO_RENDERUSERSETTINGS_H

#include <string>
#include <SDL.h>

using namespace std;

class RenderUserSettings
{
public:

    static void SetVSyncMode(bool value, bool useAdaptative = false);
    static int GetVSyncMode();

    static void SetMaxFPS(int value);
    static int GetMaxFPS();

private:
    inline static int max_fps_ = 0;
};


#endif //NANOMETRO_RENDERUSERSETTINGS_H

//
// Created by natha on 14/11/2023.
//

#ifndef NANOMETRO_TIMER_H
#define NANOMETRO_TIMER_H

#include <cstdint>
#include <SDL.h>
#include <imgui.h>

class Timer
{
    friend class RenderHardwareInterface;
public:
    Timer();
    float DeltaTime();

private:
    uint32_t elapsedTime();
};


#endif //NANOMETRO_TIMER_H

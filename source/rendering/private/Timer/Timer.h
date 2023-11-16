//
// Created by natha on 14/11/2023.
//

#ifndef NANOMETRO_TIMER_H
#define NANOMETRO_TIMER_H

#include <cstdint>
#include <SDL.h>

class Timer
{
    friend class RenderHardwareInterface;
public:
    Timer();
    float DeltaTime() const;

private:
    uint64_t previousCounter;
    void UpdateCounter();
    uint64_t elapsedTime();
};


#endif //NANOMETRO_TIMER_H

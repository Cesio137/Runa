//
// Created by natha on 14/11/2023.
//

#include "Timer.h"

Timer::Timer()
{
    
}

float Timer::DeltaTime() const
{
    float delta = static_cast<float>(SDL_GetTicks64() - previousCounter);
    return delta;
}

void Timer::UpdateCounter()
{
    previousCounter = SDL_GetTicks64();
}

uint64_t Timer::elapsedTime()
{
    uint64_t delta = SDL_GetTicks64() - previousCounter;
    return delta;
}

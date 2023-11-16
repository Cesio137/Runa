//
// Created by natha on 14/11/2023.
//

#include "Timer.h"

Timer::Timer()
{
    
}

float Timer::DeltaTime()
{
    return ImGui::GetIO().DeltaTime;
}

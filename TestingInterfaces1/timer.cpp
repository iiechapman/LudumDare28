//
//  timer.cpp
//  TestSDL2
//
//  Created by Evan Chapman on 11/17/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "timer.h"


Timer::Timer(){
    lastTime = 0;
    delta = 0;
}

Uint32 Timer::StartTimer(){
    lastTime = SDL_GetTicks();
    return lastTime;
}

Uint32 Timer::CalculateDelta(){
    delta = SDL_GetTicks() - lastTime;
    return delta;
}


Uint32 Timer::GetDelta(){
    return delta;
}

void Timer::Update(){
    CalculateDelta();
    StartTimer();
}
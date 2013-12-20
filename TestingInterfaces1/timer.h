//
//  timer.h
//  TestSDL2
//
//  Created by Evan Chapman on 11/17/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestSDL2__timer__
#define __TestSDL2__timer__

#include <iostream>
#include <SDL2/SDL.h>

class Timer{
    
public:
    
    Timer();
    
    Uint32 CalculateDelta();
    Uint32 StartTimer();
    
    void Update();
    
    //Getters + Setters
    Uint32 GetDelta();
    
private:
    //Properties
    Uint32 delta;
    Uint32 lastTime;
};



#endif /* defined(__TestSDL2__timer__) */

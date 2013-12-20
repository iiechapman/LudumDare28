//
//  MoveRight.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/5/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__MoveRight__
#define __TestingInterfaces1__MoveRight__

#include <iostream>
#include "Actor.h"

class MoveRight
{
public:
    MoveRight();
    MoveRight(int numLoops);
    MoveRight(int numLoops,int speed);
    void AttachProcess(Actor* actor);
    void PerformProcess();
    void EndProcess();
    bool IsAtEnd();
    
private:
    int m_Loops;
    int m_Speed;
    bool m_IsLooping;
    
    Actor* m_Actor;
};



#endif /* defined(__TestingInterfaces1__MoveRight__) */

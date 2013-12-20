//
//  MoveAction.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/7/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__MoveAction__
#define __TestingInterfaces1__MoveAction__

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "Actor.h"
#include "IProcess.h"

class MoveAction : public IProcess
{
public:
    MoveAction();
    MoveAction(dimensions_t displacement);
    MoveAction(dimensions_t displacement ,int numLoops);
    
    void AttachTo(Actor* actor);
    bool IsAttached();
    
    void SetLoops(int num);
    
    virtual void Perform(Uint32 deltaTime);
    void Reverse();
    
    void Undo(Uint32 deltaTime);
    
    void SetDisplacement(dimensions_t newDisplacement);
    dimensions_t GetDisplacement();
    
    void Stop();
    void Start();
    
    
    void End();
    bool IsAtEnd();
    
    GUID GetGUID();
    
    Actor* GetActor();
    
protected:
    GUID m_GUID;
    
    dimensions_t m_Displacement;
    dimensions_t m_Speed;
    
    int m_Loops;

    bool m_IsLooping;
    bool m_IsAttached;
    
    bool m_IsUpdating;

    
    int m_Ticks;
    bool m_IsReversed;
    
    Actor* m_Actor;
};

typedef vector<MoveAction*>::iterator actionIter;

#endif /* defined(__TestingInterfaces1__MoveAction__) */

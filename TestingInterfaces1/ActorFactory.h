//
//  ActorFactory.h
//  TestingInterfaces1 copy
//
//  Created by Evan Chapman on 12/13/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1_copy__ActorFactory__
#define __TestingInterfaces1_copy__ActorFactory__

#include <iostream>
#include <vector>

#include "Actor.h"

typedef vector<Actor*>::iterator actorIter;


class ActoryFactor
{
    
public:
    void AddActor(Actor* newActor);
    
    void RemoveActor(Actor* deadActor);
    
    
protected:
    void SetNumActors(unsigned long num);
    
    vector<Actor*> actors;
    unsigned long m_NumActors;

};


#endif /* defined(__TestingInterfaces1_copy__ActorFactory__) */

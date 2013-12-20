//
//  ActorFactory.cpp
//  TestingInterfaces1 copy
//
//  Created by Evan Chapman on 12/13/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "ActorFactory.h"


void ActoryFactor::AddActor(Actor* newActor)
{
    actors.push_back(newActor);
    SetNumActors(actors.size());
}


void ActoryFactor::SetNumActors(unsigned long num)
{
    m_NumActors = num;
}


void ActoryFactor::RemoveActor(Actor* deadActor)
{
    for (actorIter curr = actors.begin();
         curr != actors.end();
         curr++)
    {
        if ((*curr) == deadActor)
        {
            curr = actors.erase(curr);
        }
    }
}
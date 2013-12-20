//
//  IActorComponent.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/9/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

/*
============================
Actor Component interface

Generic top level component style , to be inherited by all potential interface objects

============================
*/

#ifndef __TestingInterfaces1__IActorComponent__
#define __TestingInterfaces1__IActorComponent__

#include <iostream>
#include <SDL2/SDL.h>
#include "Definitions.h"
#include "IGlobalID.h"

class Actor;

typedef long int ComponentID;
typedef long int TypeID;

typedef Actor* ActorHandle;

class IActorComponent
{
    
public:
    IActorComponent();
    
    bool SetOwner(ActorHandle newOwner);
    virtual void Update(Uint32 deltaTime) = 0;
    
    virtual void Init();
    
    void Sync();
    bool IsSynced();
    
protected:
    ActorHandle m_Owner;
    bool        m_Synced;
    
};


#endif /* defined(__TestingInterfaces1__IActorComponent__) */

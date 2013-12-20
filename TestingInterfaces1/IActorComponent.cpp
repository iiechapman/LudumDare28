//
//  IActorComponent.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/9/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//


#include "IActorComponent.h"




IActorComponent::IActorComponent()
{
    
}




void IActorComponent::Init()
{

}

bool IActorComponent::SetOwner(ActorHandle newOwner)
{
    //Check to see if the owner exists, if so connect to it
    if (!newOwner)
    {
        return false;
    }
    
    m_Owner = newOwner;
    
    return true;
}
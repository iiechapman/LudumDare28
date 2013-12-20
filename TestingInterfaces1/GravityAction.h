//
//  GravityAction.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/8/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__GravityAction__
#define __TestingInterfaces1__GravityAction__

#include <iostream>
#include "MoveAction.h"


class GravityAction : public MoveAction
{
public:
    GravityAction(dimensions_t dimensions);
    
    void Perform(Uint32 deltaTime);
    void SetGravity(dimensions_t newGravity);
    
    void Reset();
    
protected:
    dimensions_t m_TotalGravity;
    
    float m_GravityX , m_GravityY;
    

};


#endif /* defined(__TestingInterfaces1__GravityAction__) */

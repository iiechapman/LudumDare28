//
//  PositionComponent.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/9/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__PositionComponent__
#define __TestingInterfaces1__PositionComponent__

#include <iostream>
#include "IActorComponent.h"
#include "IGlobalID.h"
#include "Definitions.h"


class PositionComponent{

public:
    void Update(Uint32 deltaTime);
    Vec3_t GetDimensions();
    
protected:
    Vec3_t m_Dimensions;
};



#endif /* defined(__TestingInterfaces1__PositionComponent__) */

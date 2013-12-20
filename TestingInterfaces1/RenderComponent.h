//
//  RenderComponent.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/9/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__RenderComponent__
#define __TestingInterfaces1__RenderComponent__

#include <iostream>
#include "IActorComponent.h"

//Render Component needs a link to a Position component, a surface component and a color component


class RenderComponent : public IActorComponent
{

public:
    void Update(Uint32 deltaTime);
    
protected:
    bool m_IsVisible;
    bool m_IsRendered;
    
};


#endif /* defined(__TestingInterfaces1__RenderComponent__) */

//
//  ColorComponent.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/9/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__ColorComponent__
#define __TestingInterfaces1__ColorComponent__

#include <iostream>
#include "IActorComponent.h"


class ColorComponent : public IActorComponent {
    
public:
    void Update(Uint32 deltaTime);
    Color GetColor();
    
protected:
    Color m_Color;
};



#endif /* defined(__TestingInterfaces1__ColorComponent__) */

//
//  RenderableShape.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/4/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__RenderableShape__
#define __TestingInterfaces1__RenderableShape__

#include <iostream>
#include "IRenderable.h"

class RenderableShape : public IRenderable
{
    void VRender(SDL_Renderer* frame);
};



#endif /* defined(__TestingInterfaces1__RenderableShape__) */

//
//  Renderer.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/4/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__Renderer__
#define __TestingInterfaces1__Renderer__

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "IRenderable.h"

using namespace std;

class Renderer{
    
public:
    Renderer();
    void RenderToFrame(SDL_Renderer* frame);
    bool AddRenderable(IRenderable* newRenderable);
    void RemoveRenderable(IRenderable* deadRenderable);
    
    unsigned long  GetRenderablesSize();
    
private:
    vector<IRenderable*> mv_Renderables;
    
};


#endif /* defined(__TestingInterfaces1__Renderer__) */

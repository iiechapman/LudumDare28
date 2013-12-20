//
//  Renderer.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/4/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "Renderer.h"


Renderer::Renderer()
{
    printf("Created renderer...\n");
}

void Renderer::RenderToFrame(SDL_Renderer* frame)
{
    //Set background color then clear frame
    SDL_SetRenderDrawColor(frame, 0x00, 0x00, 0, 0xff);
	SDL_RenderClear(frame);
    
    typedef vector<IRenderable*>::iterator iter;
    //Iterate through all renderable objects and render them
    for(iter currentSel = mv_Renderables.begin();
        currentSel != mv_Renderables.end();
        currentSel++)
    {
        (*currentSel)->VRender(frame);
    }
    
    	SDL_RenderPresent(frame);
}


bool Renderer::AddRenderable(IRenderable* newRenderable)
{
    if (newRenderable)
    {
        mv_Renderables.push_back(newRenderable);
        return true;
    } else
        {
            return false;
        }
}


void Renderer::RemoveRenderable(IRenderable* deadRenderable)
{
    typedef vector<IRenderable*>::iterator iter;
    
    for(iter currentSel = mv_Renderables.begin();
        currentSel != mv_Renderables.end();
        )
    {
        if ((*currentSel) == deadRenderable)
        {
            currentSel = mv_Renderables.erase(currentSel);
        } else
        {
            currentSel++;
        }
    }
    
}





unsigned long  Renderer::GetRenderablesSize()
{
    return mv_Renderables.size();
}



















//
//  RenderableShape.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/4/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "RenderableShape.h"


void RenderableShape::VRender(SDL_Renderer* frame)
{
    if (GetDimensions().x >= SCREEN_WIDTH + m_CameraX ||
        GetDimensions().x <= -100||
        GetDimensions().y >= SCREEN_HEIGHT + m_CameraY ||
        GetDimensions().y <= -100)
    {
        SetVisibility(false);
    } else
    {
        SetVisibility(true);
    }
    
    if (IsVisible()) {
        Color c = GetColor();
        SDL_SetRenderDrawColor(frame, c.red, c.green, c.blue, c.alpha);
        SDL_RenderSetScale(frame, GetScaleX(), GetScaleY());
        SDL_RenderFillRect(frame, &GetRenderDimensions());

    }
}







//
//  RenderableSprite.h
//  TestingInterfaces1 copy
//
//  Created by Evan Chapman on 12/14/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1_copy__RenderableSprite__
#define __TestingInterfaces1_copy__RenderableSprite__

#include <iostream>
#include "IRenderable.h"

class RenderableSprite : public IRenderable
{
public:
    void VRender(SDL_Renderer* frame);
    void SetTexture(SDL_Texture* newTexture);
    
    void SetSrc(SDL_Rect* newSrc);
    void SetDst(SDL_Rect* newDst);
    SDL_Rect GetSrc();
    SDL_Rect GetDst();
    
    void SetFlip(SDL_RendererFlip newFlip);
    void SetAngle(double newAngle);
    void SetCenter(float x, float y);
    
private:
    SDL_Texture* m_Texture;
    SDL_Rect*   m_SrcRect;
    SDL_Rect*   m_DstRect;
    
    double m_Angle;
    SDL_Point m_Center;
    SDL_RendererFlip m_Flip;
    
    
};

#endif /* defined(__TestingInterfaces1_copy__RenderableSprite__) */

//
//  RenderableSprite.cpp
//  TestingInterfaces1 copy
//
//  Created by Evan Chapman on 12/14/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "RenderableSprite.h"


void RenderableSprite::VRender(SDL_Renderer* frame)
{
    if (GetDimensions().x >= SCREEN_WIDTH + m_CameraX ||
        GetDimensions().x <= -100||
        GetDimensions().y >= SCREEN_HEIGHT + m_CameraY||
        GetDimensions().y <= -100)
    {
        SetVisibility(false);
    } else
    {
        SetVisibility(true);
    }
    
    if (IsVisible()) {
        Color c = GetColor();
        SDL_Rect* destination = new SDL_Rect;
        
        if (GetCameraFollow())
        {
            destination->x = GetRenderDimensions().x;
            destination->y = GetRenderDimensions().y;
        } else {
            destination->x = GetDimensions().x;
            destination->y = GetDimensions().y;
        }
        
        destination->w = m_DstRect->w;
        destination->h = m_DstRect->h ;
        
        
        SDL_SetRenderDrawColor(frame, c.red, c.green, c.blue, c.alpha);
        SDL_RenderSetScale(frame, GetScaleX(), GetScaleY());
        SDL_RenderCopyEx(frame, m_Texture, m_SrcRect, destination, m_Angle, &m_Center, m_Flip);
       // SDL_RenderCopy(frame, m_Texture, m_SrcRect, m_DstRect);
        
    }
}




void RenderableSprite::SetTexture(SDL_Texture* newTexture)
{
    m_Texture = newTexture;
}


void RenderableSprite::SetSrc(SDL_Rect* newSrc)
{
    m_SrcRect = newSrc;
}

void RenderableSprite::SetDst(SDL_Rect* newDst)
{
    m_DstRect = newDst;
}

void RenderableSprite::SetFlip(SDL_RendererFlip newFlip)
{
    m_Flip = newFlip;
}

void RenderableSprite::SetAngle(double newAngle)
{
    int final = newAngle;
    
    final%= 360;
    
    m_Angle = newAngle;
}

void RenderableSprite::SetCenter(float x, float y)
{
    m_Center.x = x;
    m_Center.y = y;
}


SDL_Rect RenderableSprite::GetSrc()
{
    SDL_Rect returnRect;

    returnRect.x = m_SrcRect->x;
    returnRect.y = m_SrcRect->y;
    returnRect.w = m_SrcRect->w;
    returnRect.h = m_SrcRect->h;
    
    
    return returnRect;
}


SDL_Rect RenderableSprite::GetDst()
{
    SDL_Rect returnRect;
    
    returnRect.x = m_DstRect->x;
    returnRect.y = m_DstRect->y;
    returnRect.w = m_DstRect->w;
    returnRect.h = m_DstRect->h;
    
    
    return returnRect;
}



















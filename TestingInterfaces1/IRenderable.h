//
//  IRenderable.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/4/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__IRenderable__
#define __TestingInterfaces1__IRenderable__

#include <iostream>
#include <SDL2/SDL.h>
#include "Definitions.h"



class IRenderable{
public:
    IRenderable();
    
    virtual void VRender(SDL_Renderer* frame) = 0;
    bool IsVisible();
    
    void Update();
    void Outdate();
    
    bool IsOutdated();
    
    dimensions_t& GetDimensions();
    SDL_Rect& GetRenderDimensions();
    
    Color GetColor();
    void  SetColor(Color newColor);
    
    void SetDimensions(dimensions_t newDimensions);
    void SetVisibility(bool newVisibility);
    
    void SetScaleX(float x);
    void SetScaleY(float y);
    
    float GetScaleX();
    float GetScaleY();
    
    void SetCameraFollow(bool follow);
    bool GetCameraFollow();
    
    void SetCameraX(float x);
    void SetCameraY(float y);
    
protected:
    bool m_NeedsUpdate;
    bool m_IsVisible;
    
    bool m_FollowsCamera;
    
    float m_ScaleX;
    float m_ScaleY;
    
    float m_CameraX;
    float m_CameraY;
    
    dimensions_t m_Dimensions;
    SDL_Rect m_RenderDimensions;
    
    Color m_Color;
};


#endif /* defined(__TestingInterfaces1__IRenderable__) */

//
//  IRenderable.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/4/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "IRenderable.h"

IRenderable::IRenderable()
{
    SetScaleY(1);
    SetScaleX(1);
}


void IRenderable::SetVisibility(bool newVisibility)
{
    m_IsVisible = newVisibility;
}

void IRenderable::SetDimensions(dimensions_t newDimensions)
{
    m_Dimensions = newDimensions;
}

bool IRenderable::IsVisible()
{
    return m_IsVisible;
}


void IRenderable::Outdate()
{
    m_NeedsUpdate = true;
}


void IRenderable::Update()
{
    m_NeedsUpdate = false;
}

bool IRenderable::IsOutdated()
{
    return m_NeedsUpdate;
}

dimensions_t& IRenderable::GetDimensions()
{
    return m_Dimensions;
}


SDL_Rect& IRenderable::GetRenderDimensions()
{
    dimensions_t tempDimensions;
    
    tempDimensions = GetDimensions();
    
    m_RenderDimensions.x = tempDimensions.x - m_CameraX;
    m_RenderDimensions.y = tempDimensions.y - m_CameraY;
    m_RenderDimensions.w = tempDimensions.w;
    m_RenderDimensions.h = tempDimensions.h;
    
    return m_RenderDimensions;
}



Color IRenderable::GetColor()
{
    return m_Color;
}

void IRenderable::SetColor(Color newColor)
{
    m_Color = newColor;
}


float IRenderable::GetScaleX()
{
    return m_ScaleX;
}


float IRenderable::GetScaleY()
{
    return m_ScaleY;
}



void IRenderable::SetScaleX(float x)
{
    m_ScaleX = x;
}

void IRenderable::SetScaleY(float y)
{
    m_ScaleY = y;
}




void IRenderable::SetCameraX(float x)
{
    m_CameraX = x;
}


void IRenderable::SetCameraY(float y)
{
    m_CameraY = y;
}




void IRenderable::SetCameraFollow(bool follow)
{
    m_FollowsCamera = follow;
}

bool IRenderable::GetCameraFollow()
{
    return m_FollowsCamera;
}














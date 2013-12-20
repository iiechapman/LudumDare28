//
//  GravityAction.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/8/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "GravityAction.h"


GravityAction::GravityAction(dimensions_t dimensions) : MoveAction(dimensions)
{
    SetGravity(dimensions);
}

void GravityAction::Perform(Uint32 deltaTime)
{
    //Move Actor by X and Y displacement until loop ends
    if (IsAttached() && m_IsUpdating)
    {
        if (m_Loops != 0)
        {
            m_TotalGravity.y += m_GravityY;
            m_TotalGravity.x += m_GravityX;
    
            
            m_Actor->SetPosX(m_Actor->GetDimensions().x + (m_Displacement.x * deltaTime));
            m_Actor->SetPosY(m_Actor->GetDimensions().y + (m_TotalGravity.y * deltaTime));
            
            m_Loops--;
            
            if (!m_IsReversed)
            {
                m_Ticks++;
            } else
            {
                m_Ticks--;
            }
        }
    }
    
    //Bounds check, make sure mloops never becomes some crazy number
    if (m_Loops < 0) {
        m_Loops = -1;
    }
}


void GravityAction::SetGravity(dimensions_t newGravity)
{
    m_GravityX = newGravity.x;
    m_GravityY = newGravity.y;
}

void GravityAction::Reset()
{
    m_TotalGravity.x = 0;
    m_TotalGravity.y = 0;
}


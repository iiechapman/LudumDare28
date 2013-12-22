//
//  MoveAction.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/7/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "MoveAction.h"

MoveAction::MoveAction()
{
    dimensions_t nullDisplacement;
	nullDisplacement.x = 0;
	nullDisplacement.y = 0;
    MoveAction(nullDisplacement,0);
}

MoveAction::MoveAction(dimensions_t displacement): MoveAction(displacement ,-1){}


MoveAction::MoveAction(dimensions_t displacement , int numLoops)
{
    m_Actor = nullptr;
    m_Loops = numLoops;
    m_Displacement = displacement;
    m_IsAttached = false;
    Start();
}


void MoveAction::AttachTo(Actor* actor)
{
    if (actor)
    {
        m_Actor = actor;
        m_IsAttached = true;
    } else
        {
            m_IsAttached = false;
        }
}


bool MoveAction::IsAttached()
{
    return m_IsAttached;
}

void MoveAction::Perform(Uint32 deltaTime)
{
    //Move Actor by X and Y displacement until loop ends
    if (IsAttached() && m_IsUpdating)
    {
            m_Actor->SetPosX(m_Actor->GetDimensions().x + (m_Displacement.x * deltaTime));
            m_Actor->SetPosY(m_Actor->GetDimensions().y + (m_Displacement.y * deltaTime));
            
            m_Loops--;
            
            if (!m_IsReversed)
            {
                m_Ticks++;
            } else
            {
                m_Ticks--;
            }
        }

    
    
    //Bounds check, make sure mloops never becomes some crazy number
    if (m_Loops < 0) {
        m_Loops = -1;
    }
}

void MoveAction::Undo(Uint32 deltaTime){
    m_Displacement.x = -m_Displacement.x;
    m_Displacement.y = -m_Displacement.y;
    
    m_Actor->SetPosX(m_Actor->GetDimensions().x + (m_Displacement.x * deltaTime));
    m_Actor->SetPosY(m_Actor->GetDimensions().y + (m_Displacement.y * deltaTime));
    
}



void MoveAction::Reverse()
{
        m_Displacement.x = -m_Displacement.x;
        m_Displacement.y = -m_Displacement.y;
        m_IsReversed = !m_IsReversed;
}


void MoveAction::End()
{
    
}

bool MoveAction::IsAtEnd()
{
    return false;
}


GUID MoveAction::GetGUID()
{
    return m_GUID;
}


Actor* MoveAction::GetActor()
{
    return m_Actor;
}


void MoveAction::Stop()
{
    m_IsUpdating = false;
}

void MoveAction::Start()
{
     m_IsUpdating = true;
}


void MoveAction::SetLoops(int num)
{
    m_Loops = num;
}



void MoveAction::SetDisplacement(dimensions_t newDisplacement)
{
    m_Displacement = newDisplacement;
}

dimensions_t MoveAction::GetDisplacement()
{
    return  m_Displacement;
}

















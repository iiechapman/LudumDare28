//
//  Actor.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/4/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "Actor.h"

Actor::Actor()
{
    m_ActorView = new RenderableShape();
    
    m_Dimensions.x = 100;
    m_Dimensions.y = 100;
    m_Dimensions.w = 100;
    m_Dimensions.h = 100;

    m_Color.red = 100;
    m_Color.green = 100;
    m_Color.blue = 100;
    
    m_IsVisible = true;
    
}

IRenderable* Actor::GetActorView()
{
    return m_ActorView;
}

dimensions_t Actor::GetDimensions()
{
    return m_Dimensions;
}

void Actor::SetActorView(IRenderable* newActorView)
{
    m_ActorView = newActorView;
    UpdateView();
}

void Actor::SetColor(Color newColor)
{
    m_Color = newColor;
    UpdateView();
}

void Actor::ModelDidChange()
{
    UpdateView();
}

void Actor::SetPosY(float newPosY)
{
    m_Dimensions.y = newPosY;
    ModelDidChange();
}

void Actor::SetPosX(float newPosX)
{
    m_Dimensions.x = newPosX;
    ModelDidChange();
}

void Actor::SetWidth(float newWidth)
{
    m_Dimensions.w = newWidth;
    ModelDidChange();
}

void Actor::SetHeight(float newHeight)
{
    m_Dimensions.h = newHeight;
    ModelDidChange();
}

void Actor::Show()
{
    m_IsVisible = true;
    ModelDidChange();
}

void Actor::Hide()
{
    m_IsVisible = false;
    ModelDidChange();
}


void Actor::CheckView()
{
    if (m_ActorView->IsOutdated())
    {
        UpdateView();
    }
    m_ActorView->Update();
}


void Actor::UpdateView()
{
    UpdateViewDimensions();
    UpdateViewVisibility();
    UpdateViewColor();
    
    m_ActorView->Update();
}

void Actor::UpdateViewDimensions()
{
    m_ActorView->SetDimensions(m_Dimensions);
}


void Actor::UpdateViewVisibility()
{
    m_ActorView->SetVisibility(m_IsVisible);
}


void Actor::UpdateViewColor()
{
    m_ActorView->SetColor(m_Color);
}


bool Actor::IsInMotion()
{
    return m_InMotion;
}


void Actor::SetMotion(bool moving)
{
    m_InMotion = moving;
}



Color Actor::GetColor()
{
    return m_Color;
}


vector<MoveAction*>* Actor::GetActionList()
{
    return &m_Actions;
}



void Actor::AddAction(MoveAction* newAction)
{
    m_Actions.push_back(newAction);
}



void Actor::SetName(string newName)
{
    m_Name = newName;
}



bool Actor::IsFalling()
{
    for (actionIter i = m_Actions.begin();
         i != m_Actions.end();
         i++)
    {
        if ((*i)->GetDisplacement().y > 0){
            return true;
        }
    }

    
    return false;
}


void Actor::SetLastAction(MoveAction* lastAction)
{
    m_LastActionPerformed = lastAction;
}


MoveAction* Actor::GetLastAction()
{
    return m_LastActionPerformed;
}


void Actor::SetID(int newID)
{
    m_ID = newID;
}

int Actor::GetID()
{
    return m_ID;
}
















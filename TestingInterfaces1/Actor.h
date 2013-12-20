//
//  Actor.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/4/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__Actor__
#define __TestingInterfaces1__Actor__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include "RenderableShape.h"
#include "Definitions.h"
#include "IActorComponent.h"
#include "MoveAction.h"

using namespace std;
class MoveAction;

class Actor
{

public:
    Actor();

    dimensions_t GetDimensions();
    
    void CheckView();

    void SetPosY(float newPosY);
    void SetPosX(float newPosX);
    
    void SetWidth(float newWidth);
    void SetHeight(float newHeight);
    
    void SetColor(Color newColor);
    Color GetColor();
    
    void SetActorView(IRenderable* newActorView);
    IRenderable* GetActorView();
    
    bool IsInMotion();
    bool IsFalling();
    
    void SetMotion(bool moving);
    
    vector<MoveAction*>* GetActionList();
    void AddAction(MoveAction* newAction);
    
    void SetCameraX(float x);
    void SetCameraY(float y);
    
    void SetID(int newID);
    int GetID();
    
    void SetName(string newName);
    
    void SetLastAction(MoveAction* lastAction);
    MoveAction* GetLastAction();
    
    void Show();
    void Hide();

private:
    vector<IActorComponent*> m_Components;
    unsigned int m_NumComponents;
    
    void ModelDidChange();
    
    void UpdateView();
    void UpdateViewDimensions();
    void UpdateViewVisibility();
    void UpdateViewColor();
    
    float x,y,width,height;
    
    string m_Name;
    
    float cameraX, cameraY;
    
    //SDL_Rect    m_DimensionsOld;
    
    dimensions_t m_Dimensions;
    
    Color       m_Color;
    bool        m_IsVisible;
    
    bool        m_InMotion;
    
    IRenderable* m_ActorView;
    
    vector<MoveAction*> m_Actions;
    
    MoveAction* m_LastActionPerformed;
    
    int m_ID;
    
    
};


typedef vector<Actor*>::iterator actorIter;



#endif /* defined(__TestingInterfaces1__Actor__) */

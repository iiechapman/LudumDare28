//
//  MoveRight.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/5/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "MoveRight.h"


MoveRight::MoveRight() : MoveRight(1,1)
{
}

MoveRight::MoveRight(int speed): MoveRight(1,speed)
{
}


MoveRight::MoveRight(int numLoops,int speed)
{
    m_Speed = speed;
    m_Loops = numLoops;
}


void MoveRight::AttachProcess(Actor* actor)
{
    m_Actor = actor;
}



void MoveRight::PerformProcess()
{
    //Move actor model right
    //int posX = m_Actor->GetDimensions().x;

    if (m_Loops != 0)
    {
        m_Actor->SetPosX(m_Actor->GetDimensions().x + m_Speed);
        m_Loops--;
    }
    
    
    
}

void MoveRight::EndProcess()
{
    
}

bool MoveRight::IsAtEnd()
{
    return false;
}
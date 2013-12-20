//
//  Definitions.cpp
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/9/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "Definitions.h"


void dimensions_t::Print()
{
 
    printf("X: %f \n" , x);
    printf("Y: %f \n" , y);
    printf("W: %f \n" , w);
    printf("H: %f \n" , h);
    
    
}



void PrintRect(SDL_Rect rect)
{
    printf("X: %i \n" , rect.x);
    printf("Y: %i \n" , rect.y);
    printf("W: %i \n" , rect.w);
    printf("H: %i \n" , rect.h);
}
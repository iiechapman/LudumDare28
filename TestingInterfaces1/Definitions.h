//
//  Definitions.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/9/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__Definitions__
#define __TestingInterfaces1__Definitions__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

typedef struct dimensions_s
{
    float x;
    float y;
    float w;
    float h;
    
    void Print();
    
}dimensions_t;


typedef struct Vec3_s
{
    float x,y,z;
}Vec3_t;

void PrintRect(SDL_Rect rect);


using namespace std;

typedef struct button_s {
    bool pressed,held,released;
    string name;
    int x,y;
}button_t;


struct Color{
    int red,green,blue,alpha;
};

typedef long long GUID;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define PI 3.14159265


#define GENERIC_COMPONENT   0xF9240139A998
#define POSITION_COMPONENT  0x3F4F349CD3FD
#define COLOR_COMPONENT     0x9CE5AD47A231
#define RENDER_COMPONENT    0x5CC6AABD994B
#define AI_COMPONENT        0x77B95CCEC3D7
#define GRAVITY_COMPONENT   0xB2D8FE0F96A2

#define GRAVITY_ACTION      0xB9B415AF8439



#endif /* defined(__TestingInterfaces1__Definitions__) */

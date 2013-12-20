//
//  EventManager.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/5/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

/*
 ==========================
 EventManager
 
 Controller for Actor Objects
 Changes Actor Model, which in turn actor updates view
 
 Responds to EventCreators
 
 example:
 Player presses right arrow, input event creator creates pressed right event
 
 EventManager checks all EventReceivers to see if they handle event, if so have EventReceiver take event
 
 ==========================
 */


#ifndef __TestingInterfaces1__EventManager__
#define __TestingInterfaces1__EventManager__

#include <iostream>
#include <vector>
#include "IEventResponder.h"
using namespace std;

class EventManager
{

    
public:
    
    
private:
    vector<IEventReceiver*> mv_EventReceivers;
    
};



#endif /* defined(__TestingInterfaces1__EventManager__) */

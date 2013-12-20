//
//  IGlobalID.h
//  TestingInterfaces1
//
//  Created by Evan Chapman on 12/10/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#ifndef __TestingInterfaces1__IGlobalID__
#define __TestingInterfaces1__IGlobalID__

#include <iostream>
#include "Definitions.h"


class IGlobalID
{
public:
    GUID GetGUID();
    virtual void SetGUID() = 0;

private:
    GUID m_GUID;
    
};

#endif /* defined(__TestingInterfaces1__IGlobalID__) */

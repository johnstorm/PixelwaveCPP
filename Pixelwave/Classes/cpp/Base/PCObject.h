//
//  PCObject.h
//  Pixelwave
//
//  Created by Spiralstorm Games on 9/9/11.
//  Copyright 2011 Spiralstorm Games. All rights reserved.
//

#ifndef _PC_OBJECT_H_
#define _PC_OBJECT_H_

#include <stdio.h>
#include "PCMathUtils.h"

class PCObject
{
public:
	PCObject();
	virtual ~PCObject();

	virtual PCObject * retain();
	virtual PCObject * release();
private:
	unsigned int pcObjectRetainCount;
};

#endif

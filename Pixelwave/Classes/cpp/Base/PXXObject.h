//
//  PXXObject.h
//  Pixelwave
//
//  Created by Spiralstorm Games on 9/9/11.
//  Copyright 2011 Spiralstorm Games. All rights reserved.
//

#ifndef _PXX_OBJECT_H_
#define _PXX_OBJECT_H_

#include <stdio.h>
#include "PXXMathUtils.h"

class PXXObject
{
public:
	PXXObject();
	virtual ~PXXObject();

	virtual PXXObject * retain();
	virtual PXXObject * release();

	unsigned int retainCount();
private:
	unsigned int pxxObjectRetainCount;
};

#endif

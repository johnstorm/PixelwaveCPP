//
//  PXXObject.cpp
//  Pixelwave
//
//  Created by Spiralstorm Games on 9/9/11.
//  Copyright 2011 Spiralstorm Games. All rights reserved.
//

#include "PXXObject.h"

PXXObject::PXXObject()
{
	printf("PXXObject\n");

	pxxObjectRetainCount = 0;

	this->retain();
}

PXXObject::~PXXObject()
{
}

PXXObject * PXXObject::retain()
{
	++pxxObjectRetainCount;

	return this;
}

PXXObject * PXXObject::release()
{
	--pxxObjectRetainCount;

	if (pxxObjectRetainCount == 0)
	{
		delete this;
		return NULL;
	}

	return this;
}

unsigned int PXXObject::retainCount()
{
	return pxxObjectRetainCount;
}

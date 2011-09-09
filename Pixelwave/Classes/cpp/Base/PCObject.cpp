//
//  PCObject.cpp
//  Pixelwave
//
//  Created by Spiralstorm Games on 9/9/11.
//  Copyright 2011 Spiralstorm Games. All rights reserved.
//

#include "PCObject.h"

PCObject::PCObject()
{
	pcObjectRetainCount = 0;

	this->retain();
}

PCObject::~PCObject()
{
}

PCObject * PCObject::retain()
{
	++pcObjectRetainCount;

	return this;
}

PCObject * PCObject::release()
{
	--pcObjectRetainCount;

	if (pcObjectRetainCount == 0)
	{
		delete this;
		return NULL;
	}

	return this;
}

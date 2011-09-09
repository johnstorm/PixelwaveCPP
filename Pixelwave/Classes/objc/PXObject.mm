//
//  PXObject.m
//  Pixelwave
//
//  Created by Spiralstorm Games on 9/9/11.
//  Copyright 2011 Spiralstorm Games. All rights reserved.
//

#import "PXObject.h"

#include "PCObject.h"

@implementation PXObject

- (id) init
{
	self = [super init];

	if (self)
	{
		[self _makePXO];

		if (pxo == NULL)
		{
			[self release];
			return nil;
		}
	}

	return self;
}

- (void) dealloc
{
	if (pxo)
	{
		PCObject *pco = (PCObject *)pxo;
		pco->release();
		pxo = NULL;
	}

	[super dealloc];
}

- (void) _makePXO
{
	pxo = NULL;
}

@end

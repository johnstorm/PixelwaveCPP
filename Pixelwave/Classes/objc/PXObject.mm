//
//  PXObject.m
//  Pixelwave
//
//  Created by Spiralstorm Games on 9/9/11.
//  Copyright 2011 Spiralstorm Games. All rights reserved.
//

#import "PXObject.h"

#include "PXXObject.h"

@implementation PXObject

- (id) init
{
	self = [super init];

	if (self)
	{
		[self _makePXX];

		if (pxx == NULL)
		{
			[self release];
			return nil;
		}
	}

	return self;
}

- (void) dealloc
{
	if (pxx)
	{
		PXXObject *pxo = (PXXObject *)pxx;
		pxo->release();
		pxo = NULL;
	}

	[super dealloc];
}

- (void) _makePXX
{
	pxx = NULL;
}

@end

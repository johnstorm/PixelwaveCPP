/*
 *  _____                       ___                                            
 * /\  _ `\  __                /\_ \                                           
 * \ \ \L\ \/\_\   __  _    ___\//\ \    __  __  __    ___     __  __    ___   
 *  \ \  __/\/\ \ /\ \/ \  / __`\\ \ \  /\ \/\ \/\ \  / __`\  /\ \/\ \  / __`\ 
 *   \ \ \/  \ \ \\/>  </ /\  __/ \_\ \_\ \ \_/ \_/ \/\ \L\ \_\ \ \_/ |/\  __/ 
 *    \ \_\   \ \_\/\_/\_\\ \____\/\____\\ \___^___ /\ \__/|\_\\ \___/ \ \____\
 *     \/_/    \/_/\//\/_/ \/____/\/____/ \/__//__ /  \/__/\/_/ \/__/   \/____/
 *       
 *           www.pixelwave.org + www.spiralstormgames.com
 *                            ~;   
 *                           ,/|\.           
 *                         ,/  |\ \.                 Core Team: Oz Michaeli
 *                       ,/    | |  \                           John Lattin
 *                     ,/      | |   |
 *                   ,/        |/    |
 *                 ./__________|----'  .
 *            ,(   ___.....-,~-''-----/   ,(            ,~            ,(        
 * _.-~-.,.-'`  `_.\,.',.-'`  )_.-~-./.-'`  `_._,.',.-'`  )_.-~-.,.-'`  `_._._,.
 * 
 * Copyright (c) 2011 Spiralstorm Games http://www.spiralstormgames.com
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#import "PXTouchEvent.h"
#import "PXDisplayObject.h"
#import "PXPoint.h"

/**
 *	@ingroup Events
 *
 *	A PXTouchEvent object is dispatched into the event flow whenever a touch,
 *	release or movement occurs.  The event has information needed by the user to
 *	handle the touch correctly.
 */
@implementation PXTouchEvent

@synthesize stageX = _stageX;
@synthesize stageY = _stageY;
@synthesize nativeTouch = _nativeTouch;
@synthesize tapCount = _tapCount;

- (id) initWithType:(NSString *)type
		nativeTouch:(UITouch *)touch
			 stageX:(float)stageX
			 stageY:(float)stageY
		   tapCount:(unsigned)tapCount
{
	if (self = [super initWithType:type doesBubble:YES isCancelable:NO])
	{
		_nativeTouch = [touch retain];
		_stageX = stageX;
		_stageY = stageY;
		_tapCount = tapCount;
	}

	return self;
}

- (void) dealloc
{
	[_nativeTouch release];
	[super dealloc];
}

- (id) copyWithZone:(NSZone *)zone
{
	// TODO: Is this valid? does it return a TouchEvent???
	PXTouchEvent *event = [super copyWithZone:zone];

	event->_nativeTouch = _nativeTouch;
	event->_tapCount = _tapCount;
	event->_stageX = _stageX;
	event->_stageY = _stageY;

	return event;
}

- (NSString *)description
{
	return [NSString stringWithFormat:@"[Event type=\"%@\" bubbles=%@ cancelable=%@ stageX=%f stageY=%f]",
			_type,
			PX_BOOL_TO_STRING(_bubbles),
			PX_BOOL_TO_STRING(_cancelable),
			_stageX,
			_stageY];
}


- (PXPoint *) localPosition
{
	if (_target && [_target isKindOfClass:PXDisplayObject.class] && _target)
	{
		return [((PXDisplayObject *)_target) positionOfTouch:_nativeTouch];
	}
	
	return nil;
}

- (PXPoint *) stagePosition
{
	return [PXPoint pointWithX:_stageX andY:_stageY];
}

- (float) localX
{
	if (_target && [_target isKindOfClass:PXDisplayObject.class])
	{
		return [((PXDisplayObject *)_target) positionOfTouch:_nativeTouch].x;
	}

	return 0.0f;
}

- (float) localY
{
	if (_target && [_target isKindOfClass:PXDisplayObject.class])
	{
		return [((PXDisplayObject *)_target) positionOfTouch:_nativeTouch].y;
	}

	return 0.0f;
}

@end

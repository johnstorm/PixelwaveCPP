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

#import "PXColorTransform.h"
#include "PXXColorTransform.h"

#import "PXGLRenderer.h"

#import "PXPrivateUtils.h"

/**
 * A PXColorTransform object lets you adjust the values of each color channel
 * of a display object.
 *
 * The color of each pixel of a display object is calculated, right before
 * rendering, like so:
 * 
 * `New color value = old color value * colorMultiplier`
 *
 * _Example:_ This sample adjusts an image so that only the red color channel
 * is visible, by setting the multipliers for all the other channels to 0.
 *	PXTexture *myImage = ...
 *	
 *	...
 *	
 *	PXColorTransform *newTransform = myImage.transform.colorTransform;
 *	newTransform.redMultiplier = 1.0f;
 *	newTransform.greenMultiplier = 0.0f;
 *	newTransform.blueMultiplier = 0.0f;
 *
 *	myImage.transform.colorTransform = newTransform;
 * 
 * @see PXTransform
 */
@implementation PXColorTransform

- (void) _makePXX
{
	pxx = new PXXColorTransform();
}

- (id) init
{
	return [self initWithRedMult:1.0f
					   greenMult:1.0f
						blueMult:1.0f
					   alphaMult:1.0f];
}

/**
 * Initializes the color transform with the multipliers specified.
 *
 * @param redMultiplier The red multiplier value ranging between 0.0f and 1.0f.
 * @param greenMultiplier The green multiplier value ranging between 0.0f and 1.0f.
 * @param blueMultiplier The blue multiplier value ranging between 0.0f and 1.0f.
 * @param alphaMultiplier The alpha multiplier value ranging between 0.0f and 1.0f.
 */
- (id) initWithRedMult:(float)r greenMult:(float)g blueMult:(float)b alphaMult:(float)a
{
	self = [super init];

	if (self)
	{
		_pxToPXX(PXXColorTransform *, self)->set(r, g, b, a);
	}

	return self;
}

#pragma mark NSObject overrides

- (id) copyWithZone:(NSZone *)zone
{
	return [[[self class] allocWithZone:zone] initWithRedMult:_pxToPXX(PXXColorTransform *, self)->redMultiplier
													greenMult:_pxToPXX(PXXColorTransform *, self)->greenMultiplier
													 blueMult:_pxToPXX(PXXColorTransform *, self)->blueMultiplier
													alphaMult:_pxToPXX(PXXColorTransform *, self)->alphaMultiplier];
}

- (NSString *)description
{
	return [NSString stringWithFormat:@"(r=%f, g=%f, b=%f, a=%f)",
			_pxToPXX(PXXColorTransform *, self)->redMultiplier,
			_pxToPXX(PXXColorTransform *, self)->greenMultiplier,
			_pxToPXX(PXXColorTransform *, self)->blueMultiplier,
			_pxToPXX(PXXColorTransform *, self)->alphaMultiplier];
}

#pragma mark Pooled Reset

- (void) reset
{
	_pxToPXX(PXXColorTransform *, self)->set(1.0f, 1.0f, 1.0f, 1.0f);
}

/**
 * Sets the multipliers to their corresponding values.
 *
 * @param red The red multiplier value ranging between 0.0f and 1.0f.
 * @param green The green multiplier value ranging between 0.0f and 1.0f.
 * @param blue The blue multiplier value ranging between 0.0f and 1.0f.
 * @param alpha The alpha multiplier value ranging between 0.0f and 1.0f.
 */
- (void) setMultipliersWithRed:(float)red
						 green:(float)green
						  blue:(float)blue
						 alpha:(float)alpha
{
	_pxToPXX(PXXColorTransform *, self)->set(red, green, blue, alpha);
}

/**
 * Accepts color values ranging from 0 to 255 (a simgle byte) and sets the
 * color multipliers by converting them to percent values.
 *
 * @param red The red multiplier value ranging between 0 and 255.
 * @param green The green multiplier value ranging between 0 and 255.
 * @param blue The blue multiplier value ranging between 0 and 255.
 * @param alpha The alpha multiplier value ranging between 0 and 255.
 *
 */
- (void) setMultipliersWithRedValue:(unsigned char)red
						 greenValue:(unsigned char)green
						  blueValue:(unsigned char)blue
						 alphaValue:(unsigned char)alpha
{
	_pxToPXX(PXXColorTransform *, self)->set(red, green, blue, alpha);
}

- (void) setRedMultiplier:(float)val
{
	_pxToPXX(PXXColorTransform *, self)->redMultiplier = val;
}
- (float) redMultiplier
{
	return _pxToPXX(PXXColorTransform *, self)->redMultiplier;
}
- (void) setGreenMultiplier:(float)val
{
	_pxToPXX(PXXColorTransform *, self)->greenMultiplier = val;
}
- (float) greenMultiplier
{
	return _pxToPXX(PXXColorTransform *, self)->greenMultiplier;
}
- (void) setBlueMultiplier:(float)val
{
	_pxToPXX(PXXColorTransform *, self)->blueMultiplier = val;
}
- (float) blueMultiplier
{
	return _pxToPXX(PXXColorTransform *, self)->blueMultiplier;
}
- (void) setAlphaMultiplier:(float)val
{
	_pxToPXX(PXXColorTransform *, self)->alphaMultiplier = val;
}
- (float) alphaMultiplier
{
	return _pxToPXX(PXXColorTransform *, self)->alphaMultiplier;
}

/**
 * Creates a color transform with the multipliers specified.
 *
 * @param redMultiplier The red multiplier value ranging between 0.0f and 1.0f.
 * @param greenMultiplier The green multiplier value ranging between 0.0f and 1.0f.
 * @param blueMultiplier The blue multiplier value ranging between 0.0f and 1.0f.
 * @param alphaMultiplier The alpha multiplier value ranging between 0.0f and 1.0f.
 *
 * @return The created color transform.
 */
+ (PXColorTransform *)colorTransformWithRedMult:(float)r greenMult:(float)g blueMult:(float)b alphaMult:(float)a
{
	return [[[PXColorTransform alloc] initWithRedMult:r greenMult:g blueMult:b alphaMult:a] autorelease];
}

@end

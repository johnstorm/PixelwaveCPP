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

#import "PXVector3D.h"

#import "PXMathUtils.h"

#include "PCVector3D.h"

/**
 * A vector (or point) in a three-dimensional coordinate system,
 * where x represents the horizontal axis and y represents the vertical axis
 * and z represents the depth axis.
 */
@implementation PXVector3D

- (void) _makePXO
{
	pxo = new PCVector3D();
}

- (id) init
{
	return [self initWithX:0.0f y:0.0f z:0.0f w:0.0f];
}

/**
 * Creates a new vector at (#x, #y, #z).
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param z The depth coordinate.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f];
 *	// vector will be (5,7,4)
 */
- (id) initWithX:(float)x y:(float)y z:(float)z
{
	return [self initWithX:x y:y z:z w:0.0f];
}

/**
 * Creates a new vector at (#x, #y, #z) with rotation #w.
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param z The depth coordinate.
 * @param w The angle of rotation.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f w:0.0f];
 *	// vector will be (5,7,4) with angle of rotation 0
 */
- (id) initWithX:(float)x y:(float)y z:(float)z w:(float)w
{
	self = [super init];

	if (self)
	{
		((PCVector3D *)(self->pxo))->set(w, x, y, z);
	}

	return self;
}

#pragma mark NSObject overrides

- (id) copyWithZone:(NSZone *)zone
{
	return [[[self class] allocWithZone:zone] initWithX:((PCVector3D *)(self->pxo))->x
													  y:((PCVector3D *)(self->pxo))->y
													  z:((PCVector3D *)(self->pxo))->z
													  w:((PCVector3D *)(self->pxo))->w];
}

- (NSString *)description
{
	return [NSString stringWithFormat:@"(x=%f, y=%f, z=%f, w=%f)",
			((PCVector3D *)(self->pxo))->x,
			((PCVector3D *)(self->pxo))->y,
			((PCVector3D *)(self->pxo))->z,
			((PCVector3D *)(self->pxo))->w];
}

#pragma mark Pooled Reset

- (void) reset
{
	((PCVector3D *)(self->pxo))->set(0.0f, 0.0f, 0.0f, 0.0f);
}

#pragma mark Properties

- (void) setW:(float)val
{
	((PCVector3D *)(self->pxo))->w = val;
}
- (float) w
{
	return ((PCVector3D *)(self->pxo))->x;
}

- (void) setX:(float)val
{
	((PCVector3D *)(self->pxo))->w = val;
}
- (float) x
{
	return ((PCVector3D *)(self->pxo))->x;
}

- (void) setY:(float)val
{
	((PCVector3D *)(self->pxo))->y = val;
}
- (float) y
{
	return ((PCVector3D *)(self->pxo))->y;
}

- (void) setZ:(float)val
{
	((PCVector3D *)(self->pxo))->z = val;
}
- (float) z
{
	return ((PCVector3D *)(self->pxo))->z;
}

- (float) length
{
	return ((PCVector3D *)(self->pxo))->length();
}

- (float) lengthSquared
{
	return ((PCVector3D *)(self->pxo))->lengthSquared();
}

#pragma mark Additional Methods

/**
 * Sets the vector to (#x, #y, #z).
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param z The depth coordinate.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] init];
 *	[vector setX:5.0f y:7.0f z:4.0f];
 *	// vector will be (5,7,4) with angle of rotation 0
 */
- (void) setX:(float)x y:(float)y z:(float)z
{
	((PCVector3D *)(self->pxo))->set(x, y, z);
}

/**
 * Sets the vector to (#x, #y, #z) with rotation #w.
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param z The depth coordinate.
 * @param w The angle of rotation.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] init];
 *	[vector setX:5.0f y:7.0f z:4.0f w:0.0f];
 *	// vector will be (5,7,4) with angle of rotation 0
 */
- (void) setX:(float)x y:(float)y z:(float)z w:(float)w
{
	((PCVector3D *)(self->pxo))->set(w, x, y, z);
}

#pragma mark Flash Methods

/**
 * Adds the values of the given vector to the corresponding values of this
 * vector to create a new vector.
 *
 * @param vector The vector to be added.
 *
 * @return The created vector.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:-3.0f y:10.0f z:-9.0f];
 *	PXVector3D *vec3 = [vec1 addPoint:vec2];
 *	// vec3 will be (2.0f, 17.0f, -5.0f)
 *	PXVector3D *vec4 = [vec2 addPoint:vec3];
 *	// vec4 will be (-1.0f, 27.0f, -14.0f)
 */
- (PXVector3D *)addVector:(PXVector3D *)vector
{
	if (vector == nil)
		return nil;

	PCVector3D *vectorPXC = (PCVector3D *)(vector->pxo);
	PCVector3D ret = ((PCVector3D *)(self->pxo))->add(*vectorPXC);

	return [[[PXVector3D alloc] initWithX:ret.x y:ret.y z:ret.z w:ret.w] autorelease];
}

/**
 * Subtracts the values of the given vector to the corresponding values of this
 * vector to create a new vector.
 *
 * @param vector The vector to be added.
 *
 * @return The created vector.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:-3.0f y:10.0f z:-9.0f];
 *	PXVector3D *vec3 = [vec1 subtractVector:vec2];
 *	// vec3 will be (-8.0f, 3.0f, -13.0f)
 *	PXVector3D *vec4 = [vec2 subtractVector:vec3];
 *	// vec4 will be (-5.0f, -7.0f, -4.0f)
 */
- (PXVector3D *)subtractVector:(PXVector3D *)vector
{
	if (vector == nil)
		return nil;

	PCVector3D *vectorPXC = (PCVector3D *)(vector->pxo);
	PCVector3D ret = ((PCVector3D *)(self->pxo))->subtract(*vectorPXC);

	return [[[PXVector3D alloc] initWithX:ret.x y:ret.y z:ret.z w:ret.w] autorelease];
}

/**
 * Creates a vector that is perpendicular to the current vector and the given
 * vector.
 *
 * @param vector The other vector.
 *
 * @return The created vector.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:0.7f y:0.4f z:0.591608f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:0.3f y:-0.4f z:-0.866025f];
 *	PXVector3D *crossVector = [vec1 crossProductWithVector:vec2];
 *	// crossVector will be (-0.109767f, 0.7837f, -0.4f)
 */
- (PXVector3D *)crossProductWithVector:(PXVector3D *)vector
{
	if (vector == nil)
		return nil;

	PCVector3D *vectorPXC = (PCVector3D *)(vector->pxo);
	PCVector3D ret = ((PCVector3D *)(self->pxo))->cross(*vectorPXC);

	return [[[PXVector3D alloc] initWithX:ret.x y:ret.y z:ret.z w:ret.w] autorelease];
}

/**
 * Subtracts the values of this vector by the corresponding values of the given
 * vector.
 *
 * @param vector The vector to use for subtraction.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:-3.0f y:10.0f z:-9.0f];
 *	[vec1 decrementByVector:vec2];
 *	// vec1 will be (8.0f, -3.0f, 13.0f)
 */
- (void) decrementByVector:(PXVector3D *)vector
{
	if (vector == nil)
		return;

	PCVector3D *vectorPXC = (PCVector3D *)(vector->pxo);
	((PCVector3D *)(self->pxo))->decrement(*vectorPXC);
}

/**
 * Subtracts the values of this vector by the corresponding values of the given
 * vector.
 *
 * @param vector The vector to use for subtraction.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:-3.0f y:10.0f z:-9.0f];
 *	float dotProduct = [vec1 dotProductWithVector:vec2];
 *	// dotProduct will be 19.0f
 */
- (float) dotProductWithVector:(PXVector3D *)vector
{
	if (vector == nil)
		return 0.0f;

	PCVector3D *vectorPXC = (PCVector3D *)(vector->pxo);
	return ((PCVector3D *)(self->pxo))->dot(*vectorPXC);
}

/**
 * Check to see if this vector is equal to another.
 *
 * @param vector The vector for checking.
 * @param allFour If `YES` then #w is also used in the test, otherwise just #x, #y
 * and #z are used.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f w:0.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f w:1.0f];
 *	BOOL isEqualWithoutAllFour = [vec1 equalsVector:vec2 useAllFour:NO];
 *	BOOL isEqualWithAllFour = [vec1 equalsVector:vec2 useAllFour:YES];
 *	// isEqualWithoutAllFour will be YES, isEqualWithAllFour will be NO.
 */
- (BOOL) equalsVector:(PXVector3D *)vector useAllFour:(BOOL)allFour
{
	if (vector == nil)
		return NO;

	PCVector3D *vectorPXC = (PCVector3D *)(vector->pxo);
	return ((PCVector3D *)(self->pxo))->isEqual(*vectorPXC, allFour);
}

/**
 * Adds the values of this vector by the corresponding values of the given
 * vector.
 *
 * @param vector The vector to use for addition.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:-3.0f y:10.0f z:-9.0f];
 *	[vec1 incrementByVector:vec2];
 *	// vec1 will be (2.0f, 17.0f, -5.0f)
 */
- (void) incrementByVector:(PXVector3D *)vector
{
	if (vector == nil)
		return;

	PCVector3D *vectorPXC = (PCVector3D *)(vector->pxo);
	((PCVector3D *)(self->pxo))->increment(*vectorPXC);
}

/**
 * Check to see if each of this vector's values are within a tolerance range of
 * another
 *
 * @param vector The vector for checking.
 * @param tolerance The tolerance for the check.
 * @param allFour If `YES` then #w is also used in the test, otherwise just #x, #y
 * and #z are used.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f w:0.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:4.2f y:7.4f z:4.1f w:0.9f];
 *	BOOL isNearlyEqualByHalf = [vec1 nearEqualsVector:vec2 withTolerance:0.5f useAllFour:YES];
 *	BOOL isNearlyEqualByOne = [vec1 nearEqualsVector:vec2 withTolerance:1.0f useAllFour:YES];
 *	// isNearlyEqualByHalf will be NO, isNearlyEqualByOne will be YES.
 */
- (BOOL) nearEqualsVector:(PXVector3D *)vector tolerance:(float)tolerance useAllFour:(BOOL)allFour
{
	if (vector == nil)
		return NO;

	PCVector3D *vectorPXC = (PCVector3D *)(vector->pxo);
	return ((PCVector3D *)(self->pxo))->isNearlyEqual(*vectorPXC, tolerance, allFour);
}

/**
 * Negates the #x, #y and #z values of the vector.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f];
 *	// vector will be (5,7,4)
 *	[vector negate];
 *	// vector will be (-5,-7,-4)
 */
- (void) negate
{
	((PCVector3D *)(self->pxo))->negate();
}

/**
 * Normalizes the #x, #y and #z values of the vector.
 *
 * @return The length of the vector.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] initWithX:3.0f y:4.0f z:5.0f];
 *	// vector will be (3.0f, 4.0f, 5.0f)
 *	[vector normalize];
 *	// vector will be (0.424264f, 0.565685f, 0.707107f)
 */
- (float) normalize
{
	return ((PCVector3D *)(self->pxo))->normalize();
}

/**
 * Scales the #x, #y and #z values of the vector by `1 / ` #w.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] initWithX:3.0f y:4.0f z:5.0f w:10.0f];
 *	// vector will be (3.0f, 4.0f, 5.0f, 10.0f)
 *	[vector project];
 *	// vector will be (0.3f, 0.4f, 0.5f, 10.0f)
 */
- (void) project
{
	((PCVector3D *)(self->pxo))->project();
}

/**
 * Scales the #x, #y and #z values of the vector by the scalar.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] initWithX:3.0f y:4.0f z:5.0f];
 *	// vector will be (3.0f, 4.0f, 5.0f, 10.0f)
 *	[vector scaleBy:0.1f];
 *	// vector will be (0.3f, 0.4f, 0.5f, 10.0f)
 */
- (void) scaleBy:(float)scalar
{
	((PCVector3D *)(self->pxo))->scale(scalar);
}

/**
 * Calculates the angle (in radians) between the two given vectors.
 *
 * @param vectorA The first vector.
 * @param vectorB The second vector.
 *
 * @return The angle in radians between the two vectors.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:3.0f y:4.0f z:5.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:-4.0f y:3.0f z:5.0f];
 *	float angleInRadians = [PXVector3D angleBetweenVectorA:vec1 vectorB:vec2];
 *	// in degrees the angle is 60.0f
 */
+ (float) angleBetweenVectorA:(PXVector3D *)vectorA vectorB:(PXVector3D *)vectorB
{
	if (vectorA == nil || vectorB == nil)
		return 0.0f;

	PCVector3D *vectorAPXC = (PCVector3D *)(vectorA->pxo);
	PCVector3D *vectorBPXC = (PCVector3D *)(vectorB->pxo);

	return PCVector3D::angle(*vectorAPXC, *vectorBPXC);
}

/**
 * Calculates the distance between the two given vectors.
 *
 * @param vectorA The first vector.
 * @param vectorB The second vector.
 *
 * @return The distance between the two vectors.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:3.0f y:4.0f z:5.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:-4.0f y:3.0f z:5.0f];
 *	float distance = [PXVector3D distanceBetweenVectorA:vec1 vectorB:vec2];
 *	// The distance is 7.071068f
 */
+ (float) distanceBetweenVectorA:(PXVector3D *)vectorA vectorB:(PXVector3D *)vectorB
{
	if (vectorA == nil || vectorB == nil)
		return 0.0f;

	PCVector3D *vectorAPXC = (PCVector3D *)(vectorA->pxo);
	PCVector3D *vectorBPXC = (PCVector3D *)(vectorB->pxo);

	return PCVector3D::distance(*vectorAPXC, *vectorBPXC);
}

/**
 * Calculates the squared distance between the two given vectors.
 *
 * @param vectorA The first vector.
 * @param vectorB The second vector.
 *
 * @return The squared distance between the two vectors.
 *
 * **Example:**
 *	PXVector3D *vec1 = [[PXVector3D alloc] initWithX:3.0f y:4.0f z:5.0f];
 *	PXVector3D *vec2 = [[PXVector3D alloc] initWithX:-4.0f y:3.0f z:5.0f];
 *	float distance = [PXVector3D distanceSquaredBetweenVectorA:vec1 vectorB:vec2];
 *	// The squared distance is 50.0f
 */
+ (float) distanceSquaredBetweenVectorA:(PXVector3D *)vectorA vectorB:(PXVector3D *)vectorB
{
	if (vectorA == nil || vectorB == nil)
		return 0.0f;

	PCVector3D *vectorAPXC = (PCVector3D *)(vectorA->pxo);
	PCVector3D *vectorBPXC = (PCVector3D *)(vectorB->pxo);

	return PCVector3D::distanceSquared(*vectorAPXC, *vectorBPXC);
}

/**
 * Creates a vector at (#x, #y, #z).
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param z The depth coordinate.
 *
 * @return The created vector.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f];
 *	// vector will be (5,7,4)
 */
+ (PXVector3D *)vector3DWithX:(float)x y:(float)y z:(float)z
{
	return [PXVector3D vector3DWithX:x y:y z:z w:0.0f];
}
/**
 * Creates a new vector at (#x, #y, #z) with rotation #w.
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param z The depth coordinate.
 * @param w The angle of rotation.
 *
 * @return The created vector.
 *
 * **Example:**
 *	PXVector3D *vector = [[PXVector3D alloc] initWithX:5.0f y:7.0f z:4.0f w:0.0f];
 *	// vector will be (5,7,4) with angle of rotation 0
 */
+ (PXVector3D *)vector3DWithX:(float)x y:(float)y z:(float)z w:(float)w
{
	return [[[PXVector3D alloc] initWithX:x y:y z:z w:w] autorelease];
}

@end

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

#import "PXRectangle.h"

#import <UIKit/UIKit.h>

#import "PXPoint.h"

#include "PXXRectangle.h"
#include "PXXPoint.h"

/**
 * A PXRectangle object is an area defined by its position, as indicated by its
 * `top-left` corner (#x, #y) and by its
 * #width and its #height.
 *
 * The #x, #y, #width and
 * #height properties of the #PXRectangle class are independent of
 * each other; changing the value of one property has no effect on the others.
 * However, the #right and #bottom properties are
 * integrally related to those four properties.  For example, if you change the
 * value of the #right property, the value of the
 * #width property changes; if you change the #bottom
 * property, the value of the #height< property changes.
 *
 * The following code creates a rectangle at (0, 0) with a size of (0, 0):
 *	PXRectangle *rect = [PXRectangle new];
 *
 * The following code creates a rectangle at (10, -7) with a size of (20, 10):
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:10 y:-7 width:20 height:10];
 *
 * @see PXPoint
 */
@implementation PXRectangle

- (void) _makePXX
{
	pxx = new PXXRectangle();
}

- (id) init
{
	return [self initWithX:0.0f y:0.0f width:0.0f height:0.0f];
}

/**
 * Creates a new rectangle with `topLeft` corner at (#x,
 * #y) and size of (#width, #height).
 *
 * @param x The horizontal coordinate of the `topLeft` corner.
 * @param y The vertical coordinate of the `topLeft` corner.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 */
- (id) initWithX:(float)x y:(float)y width:(float)width height:(float)height
{
	self = [super init];

	if (self)
	{
		_pxToPXX(PXXRectangle *, self)->set(x, y, width, height);
	}

	return self;
}

#pragma mark NSObject overrides

- (id) copyWithZone:(NSZone *)zone
{
	return [[[self class] allocWithZone:zone] initWithX:_pxToPXX(PXXRectangle *, self)->x
													  y:_pxToPXX(PXXRectangle *, self)->y
												  width:_pxToPXX(PXXRectangle *, self)->width
												 height:_pxToPXX(PXXRectangle *, self)->height];
}

- (NSString *)description
{
	return [NSString stringWithFormat:@"(x=%f, y=%f, w=%f, h=%f)",
			_pxToPXX(PXXRectangle *, self)->x,
			_pxToPXX(PXXRectangle *, self)->y,
			_pxToPXX(PXXRectangle *, self)->width,
			_pxToPXX(PXXRectangle *, self)->height];
}

#pragma mark Pooled Reset

- (void) reset
{
	_pxToPXX(PXXRectangle *, self)->set(0.0f, 0.0f, 0.0f, 0.0f);
}

#pragma mark Properties

- (void) setX:(float)val
{
	_pxToPXX(PXXRectangle *, self)->x = val;
}
- (float) x
{
	return _pxToPXX(PXXRectangle *, self)->x;
}

- (void) setY:(float)val
{
	_pxToPXX(PXXRectangle *, self)->y = val;
}
- (float) y
{
	return _pxToPXX(PXXRectangle *, self)->y;
}

- (void) setWidth:(float)val
{
	_pxToPXX(PXXRectangle *, self)->width = val;
}
- (float) width
{
	return _pxToPXX(PXXRectangle *, self)->width;
}

- (void) setHeight:(float)val
{
	_pxToPXX(PXXRectangle *, self)->height = val;
}
- (float) height
{
	return _pxToPXX(PXXRectangle *, self)->height;
}

- (void) setLeft:(float)left
{
	_pxToPXX(PXXRectangle *, self)->setLeft(left);
}

- (float) left
{
	return _pxToPXX(PXXRectangle *, self)->left();
}

- (void) setRight:(float)right
{
	_pxToPXX(PXXRectangle *, self)->setRight(right);
}

- (float) right
{
	return _pxToPXX(PXXRectangle *, self)->right();
}

- (void) setTop:(float)top
{
	_pxToPXX(PXXRectangle *, self)->setTop(top);
}

- (float) top
{
	return _pxToPXX(PXXRectangle *, self)->top();
}

- (void) setBottom:(float)bottom
{
	_pxToPXX(PXXRectangle *, self)->setBottom(bottom);
}

- (float) bottom
{
	return _pxToPXX(PXXRectangle *, self)->bottom();
}

- (void) setSize:(PXPoint *)point
{
	if (point == nil)
		return;

	PXXPoint *pointPXC = _pxToPXX(PXXPoint *, point);
	_pxToPXX(PXXRectangle *, self)->setSize(*pointPXC);
}

- (PXPoint *)size
{
	PXXPoint point = _pxToPXX(PXXRectangle *, self)->size();
	return [[[PXPoint alloc] initWithX:point.x y:point.y] autorelease];
}

- (void) setBottomRight:(PXPoint *)point
{
	if (point == nil)
		return;

	PXXPoint *pointPXC = _pxToPXX(PXXPoint *, point);
	_pxToPXX(PXXRectangle *, self)->setBottomRight(*pointPXC);
}

- (PXPoint *)bottomRight
{
	PXXPoint point = _pxToPXX(PXXRectangle *, self)->bottomLeft();
	return [[[PXPoint alloc] initWithX:point.x y:point.y] autorelease];
}

- (void) setTopLeft:(PXPoint *)point
{
	if (point == nil)
		return;

	PXXPoint *pointPXC = _pxToPXX(PXXPoint *, point);
	_pxToPXX(PXXRectangle *, self)->setTopLeft(*pointPXC);
}

- (PXPoint *)topLeft
{
	PXXPoint point = _pxToPXX(PXXRectangle *, self)->topLeft();
	return [[[PXPoint alloc] initWithX:point.x y:point.y] autorelease];
}

#pragma mark Methods

/**
 * Sets the rectangle's `topLeft` corner to (#x,
 * #y) and #size of (#width, #height).
 *
 * @param x The horizontal coordinate of the `topLeft` corner.
 * @param y The vertical coordinate of the `topLeft` corner.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 *
 * **Example:**
 *	PXRectangle *rect = [PXRectangle new];
 *	// Top-left will be (0, 0) size will be (0, 0).
 *	[rect setX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 */
- (void) setX:(float)x y:(float)y width:(float)width height:(float)height
{
	_pxToPXX(PXXRectangle *, self)->set(x, y, width, height);
}

#pragma mark Flash Methods

/**
 * Determines whether the specified point is contained within the rectangle's
 * area.
 *
 * @param x The horizontal coordinate of the point.
 * @param y The vertical coordinate of the point.
 *
 * @return `YES` if the rectangle contains the point, otherwise
 * `NO`.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 *	BOOL isContained = [rect containsX:3 y:8];
 *	// isContained is YES
 */
- (BOOL) containsX:(float)x y:(float)y
{
	return _pxToPXX(PXXRectangle *, self)->contains(x, y);
}

/**
 * Determines whether the specified point is contained within the rectangle's
 * area.
 *
 * @param point The point to test.
 *
 * @return `YES` if the rectangle contains the point, otherwise
 * `NO`.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 *	PXPoint *point = [[PXPoint alloc] initWithX:3 y:8];
 *	BOOL isContained = [rect containsPoint:point];
 *	// isContained is YES
 */
- (BOOL) containsPoint:(PXPoint *)point
{
	if (point == nil)
		return NO;

	PXXPoint *pointPXX = _pxToPXX(PXXPoint *, point);
	return _pxToPXX(PXXRectangle *, self)->contains(*pointPXX);
}

/**
 * Determines whether the entire specified rectangle is contained within this
 * rectangle's area.
 *
 * @param rect The rectangle to test.
 *
 * @return `YES` if this rectangle contains the rectangle provided,
 * otherwise `NO`.
 *
 * **Example:**
 *	PXRectangle *rect1 = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// rect1 will have its top-left will be (-5, 7) size will be (10, 4).
 *	PXRectangle *rect2 = [[PXRectangle alloc] initWithX:-3 y:8 width:4 height:2];
 *	// rect2 will have its top-left will be (-3, 8) size will be (4, 2).
 *	BOOL isContained = [rect1 containsRect:rect2];
 *	// isContained is YES
 *	isContained = [rect2 containsRect:rect1];
 *	// isContained is NO
 */
- (BOOL) containsRect:(PXRectangle *)rect
{
	if (rect == nil)
		return NO;

	PXXRectangle *rectPXC = _pxToPXX(PXXRectangle *, rect);
	return _pxToPXX(PXXRectangle *, self)->contains(*rectPXC);
}

/**
 * Determines whether the rectangle specified is equal to this rectangle. This
 * is only true if the #x, #y, #width and
 * #height properties are the same.
 *
 * @param rect The rectangle to compare.
 *
 * @return `YES` if the rectangle specified is equal to this rectangle;
 * otherwise `NO`.
 *
 * **Example:**
 *	PXRectangle *rect1 = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// rect1 will have its top-left will be (-5, 7) size will be (10, 4).
 *	PXRectangle *rect2 = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// rect2 will have its top-left will be (-5, 7) size will be (10, 4).
 *	BOOL isEqual = [rect1 isEqualToRect:rect2];
 *	// isEqual is YES
 */
- (BOOL) isEqualToRect:(PXRectangle *)rect
{
	if (rect == nil)
		return NO;

	PXXRectangle *rectPXC = _pxToPXX(PXXRectangle *, rect);
	return _pxToPXX(PXXRectangle *, self)->isEqual(*rectPXC);
}

/**
 * Determines if the rectangle has an area of 0.
 *
 * @return `YES` if the rectangle has an area of 0; otherwise
 * `NO`.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	BOOL emptyRect = [rect isEmpty];
 *	// emptyRect is NO.
 *	rect.width = 0;
 *	emptyRect = [rect isEmpty];
 *	// emptyRect is YES.
 */
- (BOOL) isEmpty
{
	return _pxToPXX(PXXRectangle *, self)->isEmpty();
}

/**
 * Increases the #size of the rectangle by specified amounts
 * from the center.
 *
 * @param dx The size change in the horizontal position.
 * @param dy The size change in the vertical position.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 *	[rect inflateWithX:1 y:0.5f];
 *	// Top-left will be (-6, 6.5) size will be (12, 5).
 */
- (void) inflateWithX:(float)dx y:(float)dy
{
	_pxToPXX(PXXRectangle *, self)->inflate(dx, dy);
}

/**
 * Increases the #size of the rectangle by specified amounts
 * from the center.
 *
 * @param point The size change.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 *	PXPoint *point = [[PXPoint alloc] initWithX:1 y:0.5f];
 *	[rect inflateWithPoint:point];
 *	// Top-left will be (-6, 6.5) size will be (12, 5).
 */
- (void) inflateWithPoint:(PXPoint *)point
{
	[self inflateWithX:point.x y:point.y];
}

/**
 * If the rectangle specified interesects with this rectangle, then the
 * interesection of the two rectangles is returned as a rectangle.  Otherwise
 * an empty rectangle is returned.
 *
 * @param toIntersect The rectangle to compare.
 *
 * @return A rectangle defining the intersection of the rectangle specified, and
 * this rectangle.  It's empty if no interesection was found.
 *
 * **Example:**
 *	PXRectangle *rect1 = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// rect1 will have its top-left will be (-5, 7) size will be (10, 4).
 *	PXRectangle *rect2 = [[PXRectangle alloc] initWithX:-7 y:3 width:5 height:8];
 *	// rect2 will have its top-left will be (-7, 3) size will be (5, 8).
 *	PXRectangle *intersection = [rect1 intersectionWithRect:rect2];
 *	// intersection will have its top-left will be (-5, 7) size will be (3, 4).
 */
- (PXRectangle *)intersectionWithRect:(PXRectangle *)rect
{
	if (rect == nil)
		return nil;

	PXXRectangle *rectPXC = _pxToPXX(PXXRectangle *, rect);
	PXXRectangle ret = _pxToPXX(PXXRectangle *, self)->intersection(*rectPXC);
	return [[[PXRectangle alloc] initWithX:ret.x y:ret.y width:ret.width height:ret.height] autorelease];
}

/**
 * Determines if the rectangle specified intersects with this rectangle.
 *
 * @param toIntersect The rectangle to compare.
 *
 * @return `YES` if this rectangle intersects with the rectangle
 * specified; otherwise `NO`.
 *
 * **Example:**
 *	PXRectangle *rect1 = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// rect1 will have its top-left will be (-5, 7) size will be (10, 4).
 *	PXRectangle *rect2 = [[PXRectangle alloc] initWithX:-7 y:3 width:5 height:8];
 *	// rect2 will have its top-left will be (-7, 3) size will be (5, 8).
 *	BOOL intersects = [rect1 intersectsWithRect:rect2];
 *	// intersects is YES.
 */
- (BOOL) intersectsWithRect:(PXRectangle *)rect
{
	if (rect == nil)
		return NO;

	PXXRectangle *rectPXC = _pxToPXX(PXXRectangle *, rect);
	return _pxToPXX(PXXRectangle *, self)->intersects(*rectPXC);
}

/**
 * Adjusts the location of the rectangle.
 *
 * @param dx The horizontal change in position.
 * @param dy The vertical change in position.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 *	[rect offsetWithX:4 y:-6];
 *	// Top-left will be (-1, 1) size will be (10, 4).
 */
- (void) offsetWithX:(float)dx y:(float)dy
{
	_pxToPXX(PXXRectangle *, self)->offset(dx, dy);
}

/**
 * Adjusts the location of the rectangle.
 *
 * @param point The change in position.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 *	PXPoint *point = [[PXPoint alloc] initWithX:4 y:-6];
 *	[rect offsetWithPoint:point];
 *	// Top-left will be (-1, 1) size will be (10, 4).
 */
- (void) offsetWithPoint:(PXPoint *)point
{
	[self offsetWithX:point.x y:point.y];
}

/**
 * Sets all of the rectangle's properties to 0.
 *
 * **Example:**
 *	PXRectangle *rect = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 *	[rect setEmpty];
 *	// Top-left will be (0, 0) size will be (0, 0).
 */
- (void) setEmpty
{
	_pxToPXX(PXXRectangle *, self)->setEmpty();
}

/**
 * Adds two rectangles together to create a rectangle with their combined
 * properties.
 *
 * @param rect Rectangle to union with.
 *
 * @return The combined rectangle.
 *
 * **Example:**
 *	PXRectangle *rect1 = [[PXRectangle alloc] initWithX:-5 y:7 width:10 height:4];
 *	// rect1 will have its top-left will be (-5, 7) size will be (10, 4).
 *	PXRectangle *rect2 = [[PXRectangle alloc] initWithX:-7 y:3 width:5 height:8];
 *	// rect2 will have its top-left will be (-7, 3) size will be (5, 8).
 *	PXRectangle *unionRect = [rect1 unionWithRect:rect2];
 *	// unionRect will have its top-left will be (-7, 3) size will be (12, 8).
 */
- (PXRectangle *)unionWithRect:(PXRectangle *)rect
{
	if (rect == nil)
		return nil;

	PXXRectangle *rectPXC = _pxToPXX(PXXRectangle *, rect);
	PXXRectangle ret = _pxToPXX(PXXRectangle *, self)->unionRectangle(*rectPXC);
	return [[[PXRectangle alloc] initWithX:ret.x y:ret.y width:ret.width height:ret.height] autorelease];
}

#pragma mark Static Methods

/**
 * Creates a rectangle with `topLeft` corner at (#x,
 * #y) and #size of (#width, #height).
 *
 * @param x The horizontal coordinate of the `topLeft` corner.
 * @param y The vertical coordinate of the `topLeft` corner.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 *
 * @return The created rectangle.
 *
 * **Example:**
 *	PXRectangle *rect = [PXRectangle rectangleWithX:-5 y:7 width:10 height:4];
 *	// Top-left will be (-5, 7) size will be (10, 4).
 */
+ (PXRectangle *)rectangleWithX:(float)x y:(float)y width:(float)width height:(float)height
{
	return [[[PXRectangle alloc] initWithX:x y:y width:width height:height] autorelease];
}

@end

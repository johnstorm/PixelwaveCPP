//
//  inkGenerator.c
//  ink
//
//  Created by John Lattin on 11/16/11.
//  Copyright (c) 2011 Spiralstorm Games. All rights reserved.
//

#import "inkGenerator.h"

#include "inkFill.h"

const unsigned int inkGeneratorCurvePercision = 5;

inkGenerator* inkGeneratorCreate(inkTessellator* tessellator, void* fill)
{
	inkGenerator* generator = malloc(sizeof(inkGenerator));

	if (generator != NULL)
	{
		generator->me = generator;

		generator->tessellator = tessellator;

		generator->vertexGroupList = inkArrayCreate(sizeof(inkArray *));

		if (generator->vertexGroupList == NULL)
		{
			inkGeneratorDestroy(generator);
			return NULL;
		}

		generator->currentVertices = NULL;
		generator->fill = fill;
	}
	
	return generator;
}

void inkGeneratorDestroy(inkGenerator* generator)
{
	if (generator != NULL)
	{
		if (generator->vertexGroupList != NULL)
		{
			inkArray* array;

			inkArrayPtrForEach(generator->vertexGroupList, array)
			{
				inkArrayDestroy(array);
			}

			inkArrayDestroy(generator->vertexGroupList);
		}

		free(generator);
	}
}

void inkGeneratorMoveTo(inkGenerator* generator, inkPoint position, inkGeneratorEndFunction endFunction, void *userData)
{
	if (generator == NULL || generator->vertexGroupList == NULL)
		return;

	if (endFunction != NULL)
		endFunction(userData);
	else
		inkGeneratorEnd(generator);

	inkArray* vertices = inkArrayCreate(sizeof(INKvertex));

	if (vertices == NULL)
		return;

	inkArray** verticesPtr = inkArrayPush(generator->vertexGroupList);

	if (verticesPtr == NULL)
	{
		inkArrayDestroy(vertices);
		return;
	}

	*verticesPtr = vertices;
	generator->currentVertices = vertices;

	generator->previous = position;

	inkGeneratorAddVertex(generator, generator->previous);
}

void inkGeneratorLineTo(inkGenerator* generator, inkPoint position)
{
	if (generator == NULL)
		return;

	inkGeneratorAddVertex(generator, position);
	generator->previous = position;
}

void inkGeneratorQuadraticCurveTo(inkGenerator* generator, inkPoint control, inkPoint anchor)
{
	if (generator == NULL)
		return;

	// TODO: Implement properly instead of just making lots of LineTos

	inkPoint nextPoint;
	inkPoint d = generator->previous;
	inkPoint previousPoint = d;
	
	float tIncrement = 1.0f / (float)(inkGeneratorCurvePercision - 1);
	float t;
	float t2;

//	x = bx*t2 + cx*t +dx
//	y = by*t2 + cy*t +dy
//	with
//	dx = P0.x	dy = P0.y
//	cx = 2*P1.x-2*P0.x	cy = 2*P1.y-2*P0.y
//	bx = P2.x-2*P1.x+P0.x	by = P2.y-2*P1.y+P0.y

	inkPoint c = inkPointSubtract(inkPointScale(control, 2.0f), inkPointScale(d, 2.0f));
	inkPoint b = inkPointAdd(inkPointSubtract(anchor, inkPointScale(control, 2.0f)), d);

	unsigned int index;

	for (index = 0, t = 0.0f; index < inkGeneratorCurvePercision; ++index, t += tIncrement)
	{
		t2 = t * t;

		nextPoint = inkPointMake((b.x * t2) + (c.x * t) + d.x,
								 (b.y * t2) + (c.y * t) + d.y);

		if (inkPointIsEqual(previousPoint, nextPoint) == false)
		{
			previousPoint = nextPoint;
			
			inkGeneratorAddVertex(generator, nextPoint);
		}
	}

	/*inkPoint nextPoint;
	inkPoint previousStartPoint = generator->previous;
	inkPoint previousPoint = previousStartPoint;

	float tIncrement = 1.0f / (float)(inkGeneratorCurvePercision - 1);
	float t;
	float oneMinusT;
	float twoT;

	float pWeight;
	float cWeight;
	float aWeight;

	unsigned int index;

	for (index = 0, t = 0.0f, oneMinusT = 1.0f, twoT = t * 2.0f; index < inkGeneratorCurvePercision; ++index, t += tIncrement, oneMinusT -= tIncrement, twoT += tIncrement + tIncrement)
	{
		pWeight = oneMinusT * oneMinusT;
		cWeight = twoT * oneMinusT;
		aWeight = t * t;

		nextPoint = inkPointMake((previousStartPoint.x * pWeight) + (control.x * cWeight) + (anchor.x * aWeight),
								 (previousStartPoint.y * pWeight) + (control.y * cWeight) + (anchor.y * aWeight));

		if (inkPointIsEqual(previousPoint, nextPoint) == false)
		{
			previousPoint = nextPoint;

			inkGeneratorAddVertex(generator, nextPoint);
		}
	}*/

	generator->previous = anchor;
}

void inkGeneratorCubicCurveTo(inkGenerator* generator, inkPoint controlA, inkPoint controlB, inkPoint anchor)
{
	if (generator == NULL)
		return;

	// TODO: Implement properly instead of just making lots of LineTos

	inkPoint nextPoint;
	inkPoint d = generator->previous;
	inkPoint previousPoint = d;

	float tIncrement = 1.0f / (float)(inkGeneratorCurvePercision - 1);
	float t;
	float t2;
	float t3;

//	x = a.x*t3 + b.x*t2 + c.x*t +d.x
//	y = a.y*t3 + b.y*t2 + c.y*t +d.y
//	Where
//	dx = P0.x	dy = P0.y
//	cx = 3*P1.x-3*P0.x	cy = 3*P1.y-3*P0.y
//	bx = 3*P2.x-6*P1.x+3*P0.x	by = 3*P2.y-6*P1.y+3*P0.y
//	ax = P3.x-3*P2.x+3*P1.x-P0.x	ay = P3.y-3*P2.y+3*P1.y-P0.y

	inkPoint c = inkPointSubtract(inkPointScale(controlA, 3.0f), inkPointScale(d, 3.0f));
	inkPoint b = inkPointAdd(inkPointSubtract(inkPointScale(controlB, 3.0f), inkPointScale(controlA, 6.0f)), inkPointScale(d, 3.0f));
	inkPoint a = inkPointSubtract(inkPointAdd(inkPointSubtract(anchor, inkPointScale(controlB, 3.0f)), inkPointScale(controlA, 3.0f)), d);

	unsigned int index;

	for (index = 0, t = 0.0f; index < inkGeneratorCurvePercision; ++index, t += tIncrement)
	{
		t2 = t * t;
		t3 = t2 * t;

		nextPoint = inkPointMake((a.x * t3) + (b.x * t2) + (c.x * t) + d.x,
								 (a.y * t3) + (b.y * t2) + (c.y * t) + d.y);

		if (inkPointIsEqual(previousPoint, nextPoint) == false)
		{
			previousPoint = nextPoint;
			
			inkGeneratorAddVertex(generator, nextPoint);
		}
	}

	generator->previous = anchor;
}

void inkGeneratorEnd(inkGenerator* generator)
{
	if (generator == NULL || generator->tessellator == NULL || generator->currentVertices == NULL)
		return;

	inkTessellatorBeginContour(generator->tessellator);

	INKvertex *vertex;

	inkArrayForEach(generator->currentVertices, vertex)
	{
		inkTessellatorAddPoint(generator->tessellator, vertex);
	}

	inkTessellatorEndContour(generator->tessellator);

	generator->currentVertices = NULL;
	generator->previous = inkPointZero;
}

void inkGeneratorInitVertex(INKvertex* vertex, inkPoint position, void* fill)
{
	if (vertex == NULL)
		return;

	vertex->x = (position.x);
	vertex->y = (position.y);

	if (fill == NULL)
		return;

	inkFillType fillType = ((inkFill *)fill)->fillType;

	switch(fillType)
	{
		case inkFillType_Solid:
		{
			inkSolidFill* solidFill = (inkSolidFill *)fill;

			// TODO: Use a real color checker instead
			vertex->r = 0xFF & (solidFill->color >> 16);
			vertex->g = 0xFF & (solidFill->color >> 8);
			vertex->b = 0xFF & (solidFill->color);
			vertex->a = 0xFF * solidFill->alpha;
		}
			break;
		case inkFillType_Bitmap:
		{
			inkBitmapFill* bitmapFill = (inkBitmapFill *)fill;

			inkPoint convertedPosition = inkMatrixTransformPoint(inkMatrixInvert(bitmapFill->matrix), position);

			vertex->s = convertedPosition.x * bitmapFill->bitmapInfo.one_textureWidth;
			vertex->t = convertedPosition.y * bitmapFill->bitmapInfo.one_textureHeight;
		}
			break;
		case inkFillType_Gradient:
			// TODO: Implement
			break;
		default:
			break;
	}
}

void inkGeneratorAddVertex(inkGenerator* generator, inkPoint position)
{
	if (generator == NULL || generator->currentVertices == NULL)
		return;

	INKvertex* vertex = (INKvertex*)inkArrayPush(generator->currentVertices);

	inkGeneratorInitVertex(vertex, position, generator->fill);
}

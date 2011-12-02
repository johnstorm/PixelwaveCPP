//
//  inkStrokeGenerator.c
//  ink
//
//  Created by John Lattin on 11/8/11.
//  Copyright (c) 2011 Spiralstorm Games. All rights reserved.
//

#include "inkStrokeGenerator.h"

#include "inkTessellator.h"
#include "inkGLU.h"

#include "inkFill.h"

//#define INK_STROKE_GENERATOR_NO_FORCE_END

const unsigned int inkStrokeGeneratorRoundPrecisionPoints = 5;
// Anything less than 5 degrees will just be a line.
//const float inkStrokeGeneratorRoundAngleEpsilon = M_PI / (180 / 5);

typedef struct
{
	inkArray* vertices; // Weak
	void* fill; // Weak
} inkStrokeGeneratorRasterizeObject;

inkInline inkStrokeGeneratorRasterizeObject inkStrokeGeneratorRasterizeObjectMake(inkArray* vertices, void* fill)
{
	inkStrokeGeneratorRasterizeObject object;

	object.vertices = vertices;
	object.fill = fill;

	return object;
}

void inkStrokeGeneratorEndRasterizeGroup(inkStrokeGenerator* strokeGenerator, inkStrokeGeneratorRasterizeObject* rasterizeObject);
void inkStrokeGeneratorEndConcat(void* generator);

inkStrokeGenerator* inkStrokeGeneratorCreate(inkTessellator* tessellator, inkArray *renderGroups, inkStroke* stroke)
{
	inkStrokeGenerator* strokeGenerator = malloc(sizeof(inkStrokeGenerator));

	if (strokeGenerator != NULL)
	{
		inkGenerator* generator = inkGeneratorCreate(tessellator, NULL);

		if (generator == NULL)
		{
			inkStrokeGeneratorDestroy(strokeGenerator);
			return NULL;
		}

		strokeGenerator->rasterizeGroups = inkArrayCreate(sizeof(inkStrokeGeneratorRasterizeObject));
		if (strokeGenerator->rasterizeGroups == NULL)
		{
			inkStrokeGeneratorDestroy(strokeGenerator);
			return NULL;
		}

		strokeGenerator->generator = generator;
		strokeGenerator->stroke = stroke;

		inkTessellatorBeginPolygon(tessellator, renderGroups);
	}

	return strokeGenerator;
}

void inkStrokeGeneratorDestroy(inkStrokeGenerator* strokeGenerator)
{
	if (strokeGenerator != NULL)
	{
		if (strokeGenerator->generator != NULL)
		{
			inkTessellatorEndPolygon(strokeGenerator->generator->tessellator);

			inkArrayDestroy(strokeGenerator->rasterizeGroups);
			inkGeneratorDestroy(strokeGenerator->generator);
		}

		free(strokeGenerator);
	}
}

void inkStrokeGeneratorSetFill(inkStrokeGenerator* strokeGenerator, void* fill)
{
	if (strokeGenerator == NULL || strokeGenerator->generator == NULL)
		return;

	inkStrokeGeneratorEndConcat(strokeGenerator);

	strokeGenerator->generator->fill = fill;
}

void inkStrokeGeneratorMoveTo(inkStrokeGenerator* strokeGenerator, inkPoint position)
{
	if (strokeGenerator == NULL)
		return;

	inkGeneratorMoveTo(strokeGenerator->generator, position, inkStrokeGeneratorEndConcat, strokeGenerator);
}

void inkStrokeGeneratorLineTo(inkStrokeGenerator* strokeGenerator, inkPoint position)
{
	if (strokeGenerator == NULL)
		return;

	inkGeneratorLineTo(strokeGenerator->generator, position);
}

void inkStrokeGeneratorQuadraticCurveTo(inkStrokeGenerator* strokeGenerator, inkPoint control, inkPoint anchor)
{
	if (strokeGenerator == NULL)
		return;

	inkGeneratorQuadraticCurveTo(strokeGenerator->generator, control, anchor);
}

void inkStrokeGeneratorCubicCurveTo(inkStrokeGenerator* strokeGenerator, inkPoint controlA, inkPoint controlB, inkPoint anchor)
{
	if (strokeGenerator == NULL)
		return;

	inkGeneratorCubicCurveTo(strokeGenerator->generator, controlA, controlB, anchor);
}

inkInline void inkStrokeGeneratorAddDrawPoint(inkPoint point, inkTessellator* tessellator, void* fill)
{
	INKvertex vertex;

	inkGeneratorInitVertex(&vertex, point, fill);
	inkTessellatorVertex(&vertex, tessellator);
}

void inkStrokeGeneratorRound(inkTessellator* tessellator, void* fill, inkPoint pivotPoint, inkPoint startPoint, float startAngle, float angleDiff, float angleDist)
{
	return;
//	if (angleDiff < inkStrokeGeneratorRoundAngleEpsilon)
//		return;

	float add = angleDiff / ((float)inkStrokeGeneratorRoundPrecisionPoints + 1.0f);

	inkPoint pt0 = startPoint;
	inkPoint pt1;

	float angle = startAngle + add;

	unsigned int index;
	for (index = 0; index < inkStrokeGeneratorRoundPrecisionPoints; ++index, angle += add)
	{
		pt1 = inkPointAdd(pivotPoint, inkPointFromPolar(angleDist, angle));

		inkStrokeGeneratorAddDrawPoint(pivotPoint, tessellator, fill);
		inkStrokeGeneratorAddDrawPoint(pt0, tessellator, fill);
		inkStrokeGeneratorAddDrawPoint(pt1, tessellator, fill);
		pt0 = pt1;
	}
}

void inkStrokeGeneratorCap(inkCapsStyle style, inkTessellator* tessellator, void* fill, inkPoint pivot, inkPoint ptA, inkPoint ptB, bool reverseAngle)
{
	inkStrokeGeneratorAddDrawPoint(ptA, tessellator, fill);
	inkStrokeGeneratorAddDrawPoint(ptB, tessellator, fill);
	inkStrokeGeneratorAddDrawPoint(ptA, tessellator, fill);

	if (style != inkCapsStyle_None)
	{
		float angle = reverseAngle ? -M_PI : M_PI;
		float angleA = inkPointAngle(pivot, ptA);
		float angleDist = inkPointDistance(ptA, pivot);

		switch(style)
		{
			case inkCapsStyle_None:
				break;
			case inkCapsStyle_Round:
				inkStrokeGeneratorRound(tessellator, fill, pivot, ptA, angleA, angle, angleDist);

				inkStrokeGeneratorAddDrawPoint(pivot, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(ptB, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(ptA, tessellator, fill);

				break;
			case inkCapsStyle_Square:
			{
				inkPoint addPt = inkPointFromPolar(angleDist, angleA + (angle * 0.5f));

				inkPoint outerA = inkPointAdd(ptA, addPt);
				inkPoint outerB = inkPointAdd(ptB, addPt);

				inkStrokeGeneratorAddDrawPoint(outerB, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(outerA, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(outerA, tessellator, fill);

				inkStrokeGeneratorAddDrawPoint(ptB, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(ptA, tessellator, fill);
			}
				break;
			default:
				break;
		}
	}
}

bool inkStrokeGeneratorAdd(inkStroke* stroke, inkTessellator* tessellator, inkBox* previousBox, inkBox* nowBox, INKvertex vA, INKvertex vB, float halfScalar, void* fill, bool start, bool end, inkPoint *lastPointPtr, inkPoint* innerIntersectionPtr, bool clockwise)
{
//	printf("pt = (%f, %f)\n", vA.x, vA.y);
	inkBox box = inkBoxZero;
	// Needs to be declared and set prior to using the goto.
	bool flip = false;
	bool reverseCaps;
	bool innerOuterSwitch;
//	bool innerOuterSwitchAlreadyChecked;

	if ((stroke == NULL) || (vA.x == vB.x && vA.y == vB.y))
		goto returnStatement;

	inkPoint ptA = inkPointMake(vA.x, vA.y);
	inkPoint ptB = inkPointMake(vB.x, vB.y);
	inkPoint tempPoint;

	box = inkLineExpandToBox(inkLineMake(ptA, ptB), halfScalar);

	float baAngle = inkPointAngle(ptA, ptB);
	reverseCaps = (baAngle >= 0.0f) ^ ~clockwise;

	//stroke->caps = inkCapsStyle_Square;
	if (start == true)
	{
		inkStrokeGeneratorCap(stroke->caps, tessellator, fill, ptA, box.pointD, box.pointC, reverseCaps);
	}

	inkPoint pivotPt = ptA;

	if (previousBox != NULL)
	{
		inkPoint innerA = box.pointD;
		inkPoint innerB = previousBox->pointA;
		inkPoint outerA = box.pointC;
		inkPoint outerB = previousBox->pointB;
		if (inkPointIsEqual(outerA, outerB))
		{
			outerA = box.pointB;
			outerB = previousBox->pointC;
		}

		inkPoint* localLastPointPtr = &outerB;

		inkLine linePreviousAD = inkLineMake(previousBox->pointD, previousBox->pointA);
		inkLine linePreviousBC = inkLineMake(previousBox->pointC, previousBox->pointB);
		inkLine lineAD = inkLineMake(box.pointA, box.pointD);
		inkLine lineBC = inkLineMake(box.pointB, box.pointC);

		inkPoint innerIntersection;
		inkPoint outerIntersection;

		/*inkLine lineAB = inkLineMake(box.pointA, box.pointB);
		inkLine linePreviousCD = inkLineMake(previousBox->pointC, previousBox->pointD);

		innerIntersection = inkLineIntersection(lineAB, linePreviousCD);

		innerOuterSwitchAlreadyChecked = false;
		if (inkIsPointInLine(innerIntersection, lineAB) == false)
		{
			innerIntersection = inkLineIntersection(lineAD, linePreviousAD);
		}
		else
		{
			innerOuterSwitchAlreadyChecked = true;
		}*/
		innerIntersection = inkLineIntersection(lineAD, linePreviousAD);

		if (isnan(innerIntersection.x))
		{
			/*printf("intersection is nan between lineAD((%f, %f), (%f, %f)) and linePreviousAD((%f, %f), (%f, %f))\n",
				   lineAD.pointA.x, lineAD.pointA.y, lineAD.pointB.x, lineAD.pointB.y,
				   linePreviousAD.pointA.x, linePreviousAD.pointA.y, linePreviousAD.pointB.x, linePreviousAD.pointB.y);*/
			//box = inkBoxConcat(*previousBox, box);
			//return box;
			//return inkBoxZero;
			// TODO:	Handle a straight (or parallel) line at some point in
			//			the future.

			// NOTE:	This only needs to be done by either AD or BC
			float distAB = inkPointDistance(lineAD.pointA, linePreviousAD.pointB);
			float distBA = inkPointDistance(lineAD.pointB, linePreviousAD.pointA);

			if (distAB < distBA)
			{
				innerIntersection = inkPointScale(inkPointAdd(lineAD.pointB, linePreviousAD.pointB), 0.5f);
				outerIntersection = inkPointScale(inkPointAdd(lineBC.pointB, linePreviousBC.pointB), 0.5f);
			}
			else
			{
				innerIntersection = inkPointScale(inkPointAdd(lineAD.pointA, linePreviousAD.pointA), 0.5f);
				outerIntersection = inkPointScale(inkPointAdd(lineBC.pointA, linePreviousBC.pointA), 0.5f);
			}

			if (reverseCaps)
			{
				inkStrokeGeneratorAddDrawPoint(outerIntersection, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);
			}
			else
			{
				inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(outerIntersection, tessellator, fill);
			}

			goto endStatement;
		}
		else
		{
			/*if (innerOuterSwitchAlreadyChecked)
			{
				inkLine lineCD = inkLineMake(box.pointC, box.pointD);
				inkLine linePreviousAB = inkLineMake(previousBox->pointA, previousBox->pointB);

				outerIntersection = inkLineIntersection(lineCD, linePreviousAB);
			}
			else
			{*/
				outerIntersection = inkLineIntersection(lineBC, linePreviousBC);
			//}
		}

		inkLine lineAB = inkLineMake(box.pointA, box.pointB);
		inkLine linePreviousCD = inkLineMake(previousBox->pointC, previousBox->pointD);

		inkPoint abInnerIntersection = inkLineIntersection(lineAB, linePreviousCD);

		inkLine lineCD = inkLineMake(box.pointC, box.pointD);
		inkLine linePreviousAB = inkLineMake(previousBox->pointA, previousBox->pointB);

		inkPoint cdOuterIntersection = inkLineIntersection(lineCD, linePreviousAB);

		// Is our inner really our outer?
		//if (innerOuterSwitchAlreadyChecked == false)
		{
			float innerIntersectionDist = inkPointDistanceToLine(innerIntersection, lineAD);
			float outerIntersectionDist = inkPointDistanceToLine(outerIntersection, lineBC);
		//	float innerXIntersectionDist = inkPointDistanceToLine(abInnerIntersection, lineAB);
		//	float outerXIntersectionDist = inkPointDistanceToLine(cdOuterIntersection, lineCD);
		//	bool isInnerZero = inkIsZerof(innerIntersectionDist);
		//	bool isOuterZero = inkIsZerof(outerIntersectionDist);
		//	bool isInnerXZero = inkIsZerof(innerXIntersectionDist);
		//	bool isOuterXZero = inkIsZerof(outerXIntersectionDist);
		//	if (isInnerZero == false && inkIsZerof(outerIntersectionDist) == false)
				innerOuterSwitch = innerIntersectionDist > outerIntersectionDist;
		//	else
		//		innerOuterSwitch = !isInnerZero;

			/*if (isInnerZero == true)
			{
				innerOuterSwitch = false;
			}
			else if (isOuterZero == true)
			{
				innerOuterSwitch = true;
			}
			else if (isInnerZero == false && isOuterZero == false)
			{
				innerOuterSwitch = innerIntersectionDist > outerIntersectionDist;
				//innerOuterSwitch = ~isInnerXZero & isOuterXZero;
			}

			if (innerOuterSwitch == isInnerZero)
			{
				printf("DIFF innerIntersectionDist = %f, outerIntersectionDist = %f\n", innerIntersectionDist, outerIntersectionDist);
				printf("DIFF c innerOuterSwitch = %s, o innerOuterSwitch = %s\n", innerOuterSwitch ? "true" : "false", isInnerZero ? "false" : "true");
				printf("DIFF ab innerIntersectionDist = %f, cd outerIntersectionDist = %f\n", innerXIntersectionDist, outerXIntersectionDist);
				printf("DIFF ab in? %s, cd in? %s\n", isInnerXZero ? "true" : "false", isOuterXZero ? "true" : "false");
			}
			else
			{
			//	printf("innerIntersectionDist = %f, outerIntersectionDist = %f\n", innerIntersectionDist, outerIntersectionDist);
			//	printf("c innerOuterSwitch = %s, o innerOuterSwitch = %s\n", innerOuterSwitch ? "true" : "false", isInnerZero ? "false" : "true");
			//	printf("ab in? %s, cd in? %s\n", inkIsPointInLine(abInnerIntersection, lineAB) ? "true" : "false", inkIsPointInLine(cdOuterIntersection, lineCD) ? "true" : "false");
			}*/
		}
		//else
	//	if (innerOuterSwitchAlreadyChecked)
		//{
		//	innerOuterSwitch = false;
		//	innerOuterSwitch = inkIsZerof(outerIntersectionDist);
		//}
	//	innerOuterSwitch = isgreaterequal(innerIntersectionDist, outerIntersectionDist);
	//	innerOuterSwitch = innerIntersectionDist > outerIntersectionDist || inkIsEqualf(innerIntersectionDist, outerIntersectionDist);
	//	innerOuterSwitch = !inkIsPointInLine(innerIntersection, lineAD);

	//	if (innerOuterSwitchAlreadyChecked)
	//		innerOuterSwitch = !innerOuterSwitch;

		//bool checkAB = reverseCaps;//clockwise ^ !innerOuterSwitch;

		if (innerOuterSwitch == true)
		{
			//if (!innerOuterSwitchAlreadyChecked)
			//{
				tempPoint = innerIntersection;
				innerIntersection = outerIntersection;
				outerIntersection = tempPoint;
			//}

		//	checkAB = true;
			//tempPoint = abInnerIntersection;
			//abInnerIntersection = cdOuterIntersection;
			//cdOuterIntersection = tempPoint;

			tempPoint = innerA;
			innerA = outerA;
			outerA = tempPoint;

			tempPoint = innerB;
			innerB = outerB;
			outerB = tempPoint;
		}
		else
		{
		//	checkAB = true;
			flip = !flip;
		}

		if (reverseCaps == true)
		{
			if (inkIsPointInLine(abInnerIntersection, lineAB) == true)
				innerIntersection = abInnerIntersection;
		}
		else
		{
			if (inkIsPointInLine(cdOuterIntersection, lineCD) == true)
				innerIntersection = cdOuterIntersection;
		}

	//	if (innerDistFromPivot > 

		/*if (innerOuterSwitchAlreadyChecked && (innerIntersection.y > outerIntersection.y))
		{
			flip = !flip;
			tempPoint = innerA;
			innerA = outerA;
			outerA = tempPoint;
			
			tempPoint = innerB;
			innerB = outerB;
			outerB = tempPoint;
		}*/

		float angleA = (inkPointAngle(pivotPt, outerA));
		float angleB = (inkPointAngle(pivotPt, outerB));

		float angleDist = inkPointDistance(outerA, pivotPt);

		float angleDiff = inkAngleOrient(angleA - angleB);

		float innerDistFromPivot = inkPointDistance(pivotPt, innerIntersection);

		if (inkIsZerof(innerDistFromPivot) == false && inkIsEqualf(angleDist, innerDistFromPivot) == false)
		{
			float innerDistScale = angleDist / innerDistFromPivot;

			innerIntersection = inkPointInterpolate(pivotPt, innerIntersection, innerDistScale);
		}

		//printf("diff is %f; a = %f, b = %f\n", angleDiff * 180.0f / M_PI, angleA * 180.0f / M_PI, angleB * 180.0f / M_PI);
		if (isnan(angleDiff))
		{
			// Seriously, wtf happened?
		}

		//stroke->joints = inkJointStyle_Miter;
		float miter = stroke->miterLimit;
		if (stroke->joints == inkJointStyle_Bevel)
		{
			miter = (M_PI - angleDiff) / M_PI;
		}

		switch(stroke->joints)
		{
			/// Let bevel fall into miter, I changed the miter limit for this
			case inkJointStyle_Bevel:
			case inkJointStyle_Miter:
			{
				float dist = inkPointDistance(pivotPt, outerIntersection);
				float maxDist = stroke->thickness * miter;

				float percentDist = maxDist / dist;
				percentDist = 0.1f;
				if (percentDist > 1.0f)
					percentDist = 1.0f;

				if (inkIsEqualf(percentDist, 1.0f))
				{
					inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);
					inkStrokeGeneratorAddDrawPoint(outerIntersection, tessellator, fill);
					localLastPointPtr = &outerIntersection;
				}
				else
				{
					outerA = inkPointInterpolate(outerA, outerIntersection, percentDist);
					outerB = inkPointInterpolate(outerB, outerIntersection, percentDist);

					if (flip)
					{
						inkStrokeGeneratorAddDrawPoint(outerB, tessellator, fill);
						inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);
						inkStrokeGeneratorAddDrawPoint(outerA, tessellator, fill);
						inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);
					}
					else
					{
						inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);
						inkStrokeGeneratorAddDrawPoint(outerB, tessellator, fill);
						inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);
						inkStrokeGeneratorAddDrawPoint(outerA, tessellator, fill);
					}
				}
			}
				break;
			case inkJointStyle_Round:
			{
			/*//	inkStrokeGeneratorAddDrawPoint(outerB, tessellator, fill);
			//	inkStrokeGeneratorAddDrawPoint(pivotPt, tessellator, fill);
			//	inkStrokeGeneratorAddDrawPoint(outerA, tessellator, fill);
				inkSolidFill solidFill;
				solidFill = inkSolidFillMake(0xFF0000, 1.0f);
				inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, &solidFill);
				solidFill = inkSolidFillMake(0x00FF00, 1.0f);
				inkStrokeGeneratorAddDrawPoint(outerIntersection, tessellator, &solidFill);
				solidFill = inkSolidFillMake(0x0000FF, 1.0f);
				inkStrokeGeneratorAddDrawPoint(inkPointScale(inkPointAdd(innerIntersection, outerIntersection), 0.5f), tessellator, &solidFill);

				solidFill = inkSolidFillMake(0xFFFFFF, 1.0f);
				inkStrokeGeneratorAddDrawPoint(ptA, tessellator, &solidFill);
				solidFill = inkSolidFillMake(0xFFFFFF, 1.0f);
				inkStrokeGeneratorAddDrawPoint(ptB, tessellator, &solidFill);*/

				if (flip)
					inkStrokeGeneratorAddDrawPoint(outerB, tessellator, fill);

				inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(outerB, tessellator, fill);

				inkStrokeGeneratorRound(tessellator, fill, pivotPt, outerB, angleB, angleDiff, angleDist);

				inkStrokeGeneratorAddDrawPoint(pivotPt, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(outerA, tessellator, fill);
				inkStrokeGeneratorAddDrawPoint(innerIntersection, tessellator, fill);

				if (!flip)
					inkStrokeGeneratorAddDrawPoint(outerA, tessellator, fill);
			}
				break;
			default:
				break;
		}

		if (lastPointPtr)
			*lastPointPtr = *localLastPointPtr;
		if (innerIntersectionPtr)
			*innerIntersectionPtr = innerIntersection;
	}

endStatement:
	if (end == true)
	{
		inkStrokeGeneratorCap(stroke->caps, tessellator, fill, ptB, box.pointB, box.pointA, reverseCaps);
	}

returnStatement:
	if (nowBox != NULL)
		*nowBox = box;

	return flip;
}

void inkStrokeGeneratorEnd(inkStrokeGenerator* strokeGenerator)
{
#ifndef INK_STROKE_GENERATOR_NO_FORCE_END
	if (strokeGenerator == NULL)
		return;

	if (strokeGenerator->generator->currentVertices != NULL)
	{
		inkStrokeGeneratorEndConcat(strokeGenerator);
	}

	inkStrokeGeneratorRasterizeObject* rasterizeObject;

	inkArrayForEach(strokeGenerator->rasterizeGroups, rasterizeObject)
	{
		inkStrokeGeneratorEndRasterizeGroup(strokeGenerator, rasterizeObject);
	}

	// Make sure to clear at the end
	inkArrayClear(strokeGenerator->rasterizeGroups);
#else
	if (strokeGenerator == NULL|| strokeGenerator->generator == NULL || strokeGenerator->generator->currentVertices == NULL || strokeGenerator->generator->tessellator == NULL || strokeGenerator->stroke == NULL)
	{
		return;
	}

	inkStrokeGeneratorRasterizeObject obj = inkStrokeGeneratorRasterizeObjectMake(strokeGenerator->generator->currentVertices, strokeGenerator->generator->fill);
	inkStrokeGeneratorEndRasterizeGroup(strokeGenerator, &obj);
#endif
}

void inkStrokeGeneratorEndRasterizeGroup(inkStrokeGenerator* strokeGenerator, inkStrokeGeneratorRasterizeObject* rasterizeObject)
{
	if (strokeGenerator == NULL || rasterizeObject == NULL || strokeGenerator->generator == NULL || rasterizeObject->vertices == NULL || strokeGenerator->generator->tessellator == NULL || strokeGenerator->stroke == NULL)
	{
		return;
	}

	if (isnan(strokeGenerator->stroke->thickness))
		return;

	inkArray* vertices = rasterizeObject->vertices;

	inkGenerator* generator = strokeGenerator->generator;
	inkTessellator* tessellator = generator->tessellator;

	inkTessellatorBegin(GL_TRIANGLE_STRIP, tessellator);
//	inkTessellatorBegin(GL_LINE_LOOP, tessellator);
//	inkTessellatorBegin(GL_LINE_STRIP, tessellator);
//	inkTessellatorBegin(GL_POINTS, tessellator);

	INKvertex* vertex;

	void* fill = rasterizeObject->fill;

	INKvertex vA;
	INKvertex vB;

	inkBox previousBox;
	inkBox* previousBoxPtr = NULL;

	float halfScalar = strokeGenerator->stroke->thickness * 0.5f;

	//halfScalar = 8.0f;

	unsigned int count = inkArrayCount(vertices);

	if (count <= 1)
		return;

	vA = *((INKvertex *)(inkArrayElementAt(vertices, 0)));
	vB = *((INKvertex *)(inkArrayElementAt(vertices, count - 1)));

	bool closedLoop = inkIsEqualf(vA.x, vB.x) && inkIsEqualf(vA.y, vB.y);
	bool start = count == 2;
	bool end = start || !closedLoop;
	bool has = false;

	inkPoint lastPoint;
	inkPoint innerIntersection;

	// If count is 2, which is the minimum (it will be a line), then a will be 0
	// and b will be 1
	//vA = *((INKvertex *)(inkArrayElementAt(vertices, count - 2)));
	//vB = *((INKvertex *)(inkArrayElementAt(vertices, count - 1)));

	if (closedLoop)
	{
		if (count == 2)
			return;

		vA = *((INKvertex *)(inkArrayElementAt(vertices, count - 2)));
	}
	else
	{
		vA = vB;
	}

	bool clockwise;
	bool testHas = false;
	bool flipFirst = false;

	inkBox testBox = inkBoxZero;//inkStrokeGeneratorAdd(strokeGenerator->stroke, tessellator, previousBoxPtr, vA, vB, halfScalar, fill, start, end, NULL, NULL, false);

	//if (count > 2)
	{
	//	previousBox = testBox;
	//	previousBoxPtr = &previousBox;

		vA = vB;

		unsigned int index = 0;

		if (closedLoop)
		{
			start = false;
			end = false;
		}
	//	start = false;
	//	end = false;

		float sum = 0.0f;
		INKvertex previousVertex = *((INKvertex *)(inkArrayElementAt(vertices, 0)));

		inkArrayForEach(vertices, vertex)
		{
			if (index++ == 0)
			{
				continue;
			}

			sum += (vertex->x - previousVertex.x) * (vertex->y + previousVertex.y);
			previousVertex = *vertex;
		}

		clockwise = sum >= 0.0f;

		// Print a useful part of the .h
		/*inkPoint minPoint = inkPointMake(MAXFLOAT, MAXFLOAT);
		inkPoint maxPoint = inkPointMake(-MAXFLOAT, -MAXFLOAT);

		inkArrayForEach(vertices, vertex)
		{
			minPoint = inkPointMake(fminf(minPoint.x, vertex->x), fminf(minPoint.y, vertex->y));
			maxPoint = inkPointMake(fmaxf(maxPoint.x, vertex->x), fmaxf(maxPoint.y, vertex->y));
		}

		inkPoint midPoint = inkPointScale(inkPointAdd(minPoint, maxPoint), 0.5f);

		printf("inkPoint offset = inkPointMake(%ff, %ff);\n", midPoint.x, midPoint.y);
		printf("#define pointCount %u\ninkPoint pts[pointCount] =\n{\n", inkArrayCount(vertices));
		index = 0;
		inkArrayForEach(vertices, vertex)
		{
			printf("\tinkPointAdd(inkMatrixTransformPoint(matrix, inkPointMultiply(inkPointMake(%ff, %ff), pointMult)), offset),\n", vertex->x - midPoint.x, vertex->y - midPoint.y);
		}
		printf("};\n");*/

		index = 0;

		// TODO:	inkTessellatorVertex copies the vertex right now, make sure
		//			this will ALWAYS be the case, or this will fail.
		inkArrayForEach(vertices, vertex)
		{
			vB = *vertex;

			if (index == 0)
				goto continueStatement;

			if (closedLoop == false)
			{
				start = (index == 1);
				end = (index == count - 1);
			}

			if (has == true || index == 1)
			{
				inkStrokeGeneratorAdd(strokeGenerator->stroke, tessellator, previousBoxPtr, &testBox, vA, vB, halfScalar, fill, start, end, NULL, NULL, clockwise);
				previousBoxPtr = &previousBox;
			}
			else
			{
				testHas = true;
				flipFirst = inkStrokeGeneratorAdd(strokeGenerator->stroke, tessellator, previousBoxPtr, &testBox, vA, vB, halfScalar, fill, start, end, &lastPoint, &innerIntersection, clockwise);
			}

			if (inkBoxIsEqual(testBox, inkBoxZero) == false)
			{
				previousBox = testBox;
				if (testHas == true)
				{
					testHas = false;
					has = true;
				}
			}
			else if (testHas == true)
			{
				testHas = false;
				has = false;
			}

		//	else
		//		testBox = inkStrokeGeneratorAdd(strokeGenerator->stroke, tessellator, previousBoxPtr, vA, vB, halfScalar, fill, start, end, NULL, NULL, clockwise);
		continueStatement:
			vA = vB;
			++index;
		}

		if (closedLoop)
		{
			vB = *((INKvertex *)(inkArrayElementAt(vertices, 1)));
			inkStrokeGeneratorAdd(strokeGenerator->stroke, tessellator, previousBoxPtr, NULL, vA, vB, halfScalar, fill, false, false, NULL, NULL, clockwise);

			if (flipFirst == true)
			{
				inkGeneratorInitVertex(&vA, lastPoint, fill);
				inkTessellatorVertex(&vA, tessellator);
			}

			inkGeneratorInitVertex(&vA, innerIntersection, fill);
			inkTessellatorVertex(&vA, tessellator);

			if (flipFirst == false)
			{
				inkGeneratorInitVertex(&vA, lastPoint, fill);
				inkTessellatorVertex(&vA, tessellator);
			}
		}
	}

	inkTessellatorEnd(tessellator);
}

void inkStrokeGeneratorEndConcat(void* generator)
{
#ifndef INK_STROKE_GENERATOR_NO_FORCE_END
	inkStrokeGenerator* strokeGenerator = (inkStrokeGenerator*)generator;

	if (strokeGenerator == NULL || strokeGenerator->generator == NULL || strokeGenerator->generator->currentVertices == NULL)
	{
		return;
	}

	if (inkArrayCount(strokeGenerator->generator->currentVertices) == 0)
		return;

	inkStrokeGeneratorRasterizeObject* rasterizeObject = inkArrayPush(strokeGenerator->rasterizeGroups);
	if (rasterizeObject == NULL)
		return;

	*rasterizeObject = inkStrokeGeneratorRasterizeObjectMake(strokeGenerator->generator->currentVertices, strokeGenerator->generator->fill);
	strokeGenerator->generator->currentVertices = NULL;
#else
	inkStrokeGeneratorEnd((inkStrokeGenerator*)generator);
#endif
}

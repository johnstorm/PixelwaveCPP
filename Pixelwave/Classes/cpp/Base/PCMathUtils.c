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

#include "PCMathUtils.h"

static const float pcMathUtilsOneOverMaxRand = 1.0f / ((float)RAND_MAX + 1);

bool PCMathIsNan(float val)
{
	return isnan(val);
}

float PCMathRandom()
{
	return rand() * pcMathUtilsOneOverMaxRand;
}

float PCMathFloatInRange(float min, float max)
{
	float newMin = PCMathMin(min, max);
	float newMax = PCMathMax(min, max);

	return ((newMax - newMin) * PCMathRandom()) + newMin;
}

int PCMathIntInRange(int min, int max)
{
	int newMin = PCMathMin(min, max);
	int newMax = PCMathMax(min, max);

	return rand() % (newMax - newMin + 1) + newMin;
}

void PCMathSeedRandomWithTime()
{
	srand(time(NULL));
}

void PCMathSeedRandomWithValue(unsigned value)
{
	srand(value);
}

float PCMathLog(float val, float base)
{
	return logf(val) / logf(base);
}

bool PCMathPointInLine(PCMathPoint *ans, PCMathPoint *point, PCMathLine *line)
{
	float x1 = line->pointA.x;
	float y1 = line->pointA.y;
	float x2 = line->pointB.x;
	float y2 = line->pointB.y;

	float xDelta = x2 - x1;
	float yDelta = y2 - y1;

	if (PCMathIsZero(xDelta) && PCMathIsZero(yDelta))
		return false;

	float x3 = point->x;
	float y3 = point->y;

	float u = (((x3 - x1) * xDelta) + ((y3 - y1) * yDelta))
	          / ((xDelta * xDelta) + (yDelta * yDelta));

	if (u < 0.0f)
	{
		ans->x = x1;
		ans->y = y1;
	}
	else if (u > 1.0f)
	{
		ans->x = x2;
		ans->y = y2;
	}
	else
	{
		ans->x = x1 + (u * (x2 - x1));
		ans->y = y1 + (u * (y2 - y1));
	}

	return true;
}

float PCMathPointDistanceToLine(PCMathPoint *point, PCMathLine *line)
{
	PCMathPoint pointOnLine;
	if (!PCMathPointInLine(&pointOnLine, point, line))
		return PCMathPointDist(line->pointA, *point);

	return PCMathPointDist(pointOnLine, *point);
}

float PCMathLerpf(float start, float end, float percent)
{
	return (start * (1.0f - percent)) + (end * percent);
}

int32_t PCMathNextPowerOfTwo(int32_t val)
{
	val -= 1;
		val |= (val >> 1);
		val |= (val >> 2);
		val |= (val >> 4);
		val |= (val >> 8);
		val |= (val >> 16);
	val += 1;

	return val;
}

int64_t PCMathNextPowerOfTwo64(int64_t val)
{
	val -= 1;
		val |= (val >> 1);
		val |= (val >> 2);
		val |= (val >> 4);
		val |= (val >> 8);
		val |= (val >> 16);
		val |= (val >> 32);
	val += 1;

	return val;
}

bool PCMathIsPointInLine(PCMathPoint *point, PCMathLine *line)
{
	return PCMathIsZero(PCMathPointDistanceToLine(point, line));
}

// Barycentric Technique
bool PCMathIsPointInTriangle(PCMathPoint *point, PCMathTriangle *triangle)
{
	// Compute vectors
	float pX = point->x;
	float pY = point->y;
	float aX = triangle->pointA.x;
	float aY = triangle->pointA.y;
	float bX = triangle->pointB.x;
	float bY = triangle->pointB.y;
	float cX = triangle->pointC.x;
	float cY = triangle->pointC.y;

	//PCMathPoint v0; // C - A
	PCMathPoint v0 = PCMathPointMake(cX - aX, cY - aY);
	//PCMathPoint v1; // B - A
	PCMathPoint v1 = PCMathPointMake(bX - aX, bY - aY);
	//PCMathPoint v2; // P - A
	PCMathPoint v2 = PCMathPointMake(pX - aX, pY - aY);

	// Compute dot products
	float dot00 = PCMathPointDot(v0, v0);
	float dot01 = PCMathPointDot(v0, v1);
	float dot02 = PCMathPointDot(v0, v2);
	float dot11 = PCMathPointDot(v1, v1);
	float dot12 = PCMathPointDot(v1, v2);

	// Compute barycentric coordinates
	float denom = ((dot00 * dot11) - (dot01 * dot01));
	if (PCMathIsZero(denom))
		return false;

	float invDenom = 1.0f / denom;
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	return (u >= 0) && (v >= 0) && (u + v <= 1);
}

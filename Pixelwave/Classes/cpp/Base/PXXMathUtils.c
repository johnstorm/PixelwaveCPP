
#include "PXXMathUtils.h"

static const float pxxMathUtilsOneOverMaxRand = 1.0f / ((float)RAND_MAX + 1);

bool PXXMathIsNan(float val)
{
	return isnan(val);
}

float PXXMathRandom()
{
	return rand() * pxxMathUtilsOneOverMaxRand;
}

float PXXMathFloatInRange(float min, float max)
{
	float newMin = PXXMathMin(min, max);
	float newMax = PXXMathMax(min, max);

	return ((newMax - newMin) * PXXMathRandom()) + newMin;
}

int PXXMathIntInRange(int min, int max)
{
	int newMin = PXXMathMin(min, max);
	int newMax = PXXMathMax(min, max);

	return rand() % (newMax - newMin + 1) + newMin;
}

void PXXMathSeedRandomWithTime()
{
	srand(time(NULL));
}

void PXXMathSeedRandomWithValue(unsigned value)
{
	srand(value);
}

float PXXMathLog(float val, float base)
{
	return logf(val) / logf(base);
}

bool PXXMathPointInLine(PXXMathPoint *ans, PXXMathPoint *point, PXXMathLine *line)
{
	float x1 = line->pointA.x;
	float y1 = line->pointA.y;
	float x2 = line->pointB.x;
	float y2 = line->pointB.y;

	float xDelta = x2 - x1;
	float yDelta = y2 - y1;

	if (PXXMathIsZero(xDelta) && PXXMathIsZero(yDelta))
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

float PXXMathPointDistanceToLine(PXXMathPoint *point, PXXMathLine *line)
{
	PXXMathPoint pointOnLine;
	if (!PXXMathPointInLine(&pointOnLine, point, line))
		return PXXMathPointDist(line->pointA, *point);

	return PXXMathPointDist(pointOnLine, *point);
}

float PXXMathLerpf(float start, float end, float percent)
{
	return (start * (1.0f - percent)) + (end * percent);
}

int32_t PXXMathNextPowerOfTwo(int32_t val)
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

int64_t PXXMathNextPowerOfTwo64(int64_t val)
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

bool PXXMathIsPointInLine(PXXMathPoint *point, PXXMathLine *line)
{
	return PXXMathIsZero(PXXMathPointDistanceToLine(point, line));
}

// Barycentric Technique
bool PXXMathIsPointInTriangle(PXXMathPoint *point, PXXMathTriangle *triangle)
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

	//PXXMathPoint v0; // C - A
	PXXMathPoint v0 = PXXMathPointMake(cX - aX, cY - aY);
	//PXXMathPoint v1; // B - A
	PXXMathPoint v1 = PXXMathPointMake(bX - aX, bY - aY);
	//PXXMathPoint v2; // P - A
	PXXMathPoint v2 = PXXMathPointMake(pX - aX, pY - aY);

	// Compute dot products
	float dot00 = PXXMathPointDot(v0, v0);
	float dot01 = PXXMathPointDot(v0, v1);
	float dot02 = PXXMathPointDot(v0, v2);
	float dot11 = PXXMathPointDot(v1, v1);
	float dot12 = PXXMathPointDot(v1, v2);

	// Compute barycentric coordinates
	float denom = ((dot00 * dot11) - (dot01 * dot01));
	if (PXXMathIsZero(denom))
		return false;

	float invDenom = 1.0f / denom;
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	return (u >= 0) && (v >= 0) && (u + v <= 1);
}

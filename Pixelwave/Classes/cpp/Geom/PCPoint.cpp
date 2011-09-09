
#include "PCPoint.h"

static float pcPointComparePercision = 1000000.0f;

PCPoint::PCPoint()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

PCPoint::PCPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

PCPoint::PCPoint(PCPoint * point)
{
	this->x = point->x;
	this->y = point->y;
}

void PCPoint::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

float PCPoint::length()
{
	return sqrtf((x * x) + (y * y));
}

PCPoint PCPoint::add(PCPoint point)
{
	return PCPoint(x + point.x, y + point.y);
}
PCPoint PCPoint::subtract(PCPoint point)
{
	return PCPoint(x - point.x, y - point.y);
}

bool PCPoint::isEqual(PCPoint point)
{
	if (PCMathIsEqual(x, point.x) && PCMathIsEqual(y, point.y))
	{
		return true;
	}

	return false;
}

void PCPoint::normalize()
{
	float length = sqrtf(x * x + y * y);

	if (PCMathIsZero(length))
		return;

	length = 1.0f / length;

	x *= length;
	y *= length;
}

void PCPoint::normalize(float length)
{
	this->normalize();

	x *= length;
	y *= length;
}
void PCPoint::offset(float dx, float dy)
{
	x += dx;
	y += dy;
}

float PCPoint::distance(PCPoint pointA, PCPoint pointB)
{
	float x = pointB.x - pointA.x;
	float y = pointB.y - pointA.y;

	return sqrtf((x * x) + (y * y));
}
float PCPoint::angle(PCPoint pointA, PCPoint pointB)
{
	float angle = atan2f(pointB.y - pointA.y, pointB.x - pointA.x);

	return PCMathToDeg(angle) + 90.0f;
}
PCPoint PCPoint::interpolate(PCPoint pointA, PCPoint pointB, float coefficient)
{
	PCPoint point = PCPoint(pointB);

	PCPoint deltaPoint = PCPoint((pointA.x - point.x) * coefficient, (pointA.y - point.y) * coefficient);

	return point.add(deltaPoint);
}
PCPoint PCPoint::polar(float len, float angle)
{
	return PCPoint(cosf(angle) * len, sinf(angle) * len);
}

int PCPoint::compareX(const void *elm1, const void *elm2)
{
	const PCPoint *pt1 = (const PCPoint *)(elm1);
	const PCPoint *pt2 = (const PCPoint *)(elm2);

	return (pt1->x * pcPointComparePercision) - (pt2->x * pcPointComparePercision);
}

int PCPoint::compareY(const void *elm1, const void *elm2)
{
	const PCPoint *pt1 = (const PCPoint *)(elm1);
	const PCPoint *pt2 = (const PCPoint *)(elm2);

	return (pt1->y * pcPointComparePercision) - (pt2->y * pcPointComparePercision);
}


#include "PXXPoint.h"

static float pxxPointComparePercision = 1000000.0f;

PXXPoint::PXXPoint()
{
	printf("pxxpoint\n");

	this->x = 0.0f;
	this->y = 0.0f;
}

PXXPoint::PXXPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

PXXPoint::PXXPoint(PXXPoint * point)
{
	this->x = point->x;
	this->y = point->y;
}

void PXXPoint::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

float PXXPoint::length()
{
	return sqrtf((x * x) + (y * y));
}

PXXPoint PXXPoint::add(PXXPoint point)
{
	return PXXPoint(x + point.x, y + point.y);
}
PXXPoint PXXPoint::subtract(PXXPoint point)
{
	return PXXPoint(x - point.x, y - point.y);
}

bool PXXPoint::isEqual(PXXPoint point)
{
	if (PXXMathIsEqual(x, point.x) && PXXMathIsEqual(y, point.y))
	{
		return true;
	}

	return false;
}

void PXXPoint::normalize()
{
	float length = sqrtf(x * x + y * y);

	if (PXXMathIsZero(length))
		return;

	length = 1.0f / length;

	x *= length;
	y *= length;
}

void PXXPoint::normalize(float length)
{
	this->normalize();

	x *= length;
	y *= length;
}
void PXXPoint::offset(float dx, float dy)
{
	x += dx;
	y += dy;
}

float PXXPoint::distance(PXXPoint pointA, PXXPoint pointB)
{
	float x = pointB.x - pointA.x;
	float y = pointB.y - pointA.y;

	return sqrtf((x * x) + (y * y));
}
float PXXPoint::angle(PXXPoint pointA, PXXPoint pointB)
{
	float angle = atan2f(pointB.y - pointA.y, pointB.x - pointA.x);

	return PXXMathToDeg(angle) + 90.0f;
}
PXXPoint PXXPoint::interpolate(PXXPoint pointA, PXXPoint pointB, float coefficient)
{
	PXXPoint point = PXXPoint(pointB);

	PXXPoint deltaPoint = PXXPoint((pointA.x - point.x) * coefficient, (pointA.y - point.y) * coefficient);

	return point.add(deltaPoint);
}
PXXPoint PXXPoint::polar(float len, float angle)
{
	return PXXPoint(cosf(angle) * len, sinf(angle) * len);
}

int PXXPoint::compareX(const void *elm1, const void *elm2)
{
	const PXXPoint *pt1 = (const PXXPoint *)(elm1);
	const PXXPoint *pt2 = (const PXXPoint *)(elm2);

	return (pt1->x * pxxPointComparePercision) - (pt2->x * pxxPointComparePercision);
}

int PXXPoint::compareY(const void *elm1, const void *elm2)
{
	const PXXPoint *pt1 = (const PXXPoint *)(elm1);
	const PXXPoint *pt2 = (const PXXPoint *)(elm2);

	return (pt1->y * pxxPointComparePercision) - (pt2->y * pxxPointComparePercision);
}

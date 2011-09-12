
#ifndef _PXX_POINT_H_
#define _PXX_POINT_H_

#include "PXXObject.h"

class PXXPoint : public PXXObject
{
public:
	float x;
	float y;

	PXXPoint();
	PXXPoint(float x, float y);
	PXXPoint(PXXPoint * point);

	void set(float x, float y);

	float length();

	PXXPoint add(PXXPoint point);
	PXXPoint subtract(PXXPoint point);

	bool isEqual(PXXPoint point);
	void normalize();
	void normalize(float length);
	void offset(float dx, float dy);

	static float distance(PXXPoint pointA, PXXPoint pointB);
	static float angle(PXXPoint pointA, PXXPoint pointB);
	static PXXPoint interpolate(PXXPoint pointA, PXXPoint pointB, float coefficient);
	static PXXPoint polar(float len, float angle);

	static int compareX(const void *elm1, const void *elm2);
	static int compareY(const void *elm1, const void *elm2);
};

#endif

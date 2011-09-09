
#ifndef _PC_POINT_H_
#define _PC_POINT_H_

#include "PCObject.h"

class PCPoint : public PCObject
{
public:
	float x;
	float y;

	PCPoint();
	PCPoint(float x, float y);
	PCPoint(PCPoint * point);

	void set(float x, float y);

	float length();

	PCPoint add(PCPoint point);
	PCPoint subtract(PCPoint point);

	bool isEqual(PCPoint point);
	void normalize();
	void normalize(float length);
	void offset(float dx, float dy);

	static float distance(PCPoint pointA, PCPoint pointB);
	static float angle(PCPoint pointA, PCPoint pointB);
	static PCPoint interpolate(PCPoint pointA, PCPoint pointB, float coefficient);
	static PCPoint polar(float len, float angle);

	static int compareX(const void *elm1, const void *elm2);
	static int compareY(const void *elm1, const void *elm2);
};

#endif

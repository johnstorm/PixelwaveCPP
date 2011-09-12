
#ifndef _PXX_VECTOR_3D_H_
#define _PXX_VECTOR_3D_H_

#include "PXXObject.h"

class PXXVector3D : public PXXObject
{
public:
	float w;
	float x;
	float y;
	float z;

	PXXVector3D();
	PXXVector3D(float x, float y, float z);
	PXXVector3D(float w, float x, float y, float z);
	PXXVector3D(PXXVector3D * vector);

	void set(float x, float y, float z);
	void set(float w, float x, float y, float z);

	float length();
	float lengthSquared();

	PXXVector3D add(PXXVector3D vector);
	PXXVector3D subtract(PXXVector3D vector);
	PXXVector3D cross(PXXVector3D vector);

	void increment(PXXVector3D vector);
	void decrement(PXXVector3D vector);

	bool isEqual(PXXVector3D vector, bool allFour = false);
	bool isNearlyEqual(PXXVector3D vector, float tolerance, bool allFour = false);

	float dot(PXXVector3D vector);
	void negate();
	float normalize();
	void project();
	void scale(float scalar);

	static float angle(PXXVector3D vectorA, PXXVector3D vectorB);
	static float distance(PXXVector3D vectorA, PXXVector3D vectorB);
	static float distanceSquared(PXXVector3D vectorA, PXXVector3D vectorB);
};

#endif


#ifndef _PC_VECTOR_3D_H_
#define _PC_VECTOR_3D_H_

#include "PCObject.h"

class PCVector3D : public PCObject
{
public:
	float w;
	float x;
	float y;
	float z;

	PCVector3D();
	PCVector3D(float x, float y, float z);
	PCVector3D(float w, float x, float y, float z);
	PCVector3D(PCVector3D * vector);

	void set(float x, float y, float z);
	void set(float w, float x, float y, float z);

	float length();
	float lengthSquared();

	PCVector3D add(PCVector3D vector);
	PCVector3D subtract(PCVector3D vector);
	PCVector3D cross(PCVector3D vector);

	void increment(PCVector3D vector);
	void decrement(PCVector3D vector);

	bool isEqual(PCVector3D vector, bool allFour = false);
	bool isNearlyEqual(PCVector3D vector, float tolerance, bool allFour = false);

	float dot(PCVector3D vector);
	void negate();
	float normalize();
	void project();
	void scale(float scalar);

	static float angle(PCVector3D vectorA, PCVector3D vectorB);
	static float distance(PCVector3D vectorA, PCVector3D vectorB);
	static float distanceSquared(PCVector3D vectorA, PCVector3D vectorB);
};

#endif


#ifndef _PC_MATRIX_H_
#define _PC_MATRIX_H_

#include "PCObject.h"

class PCPoint;

class PCMatrix : public PCObject
{
public:
	float a;
	float b;
	float c;
	float d;
	float tx;
	float ty;

	PCMatrix();
	PCMatrix(float a, float b, float c, float d, float tx, float ty);
	PCMatrix(PCMatrix * matrix);

	void set(float a, float b, float c, float d, float tx, float ty);

	void concat(PCMatrix matrix);
	void identity();
	void invert();
	void rotate(float angle);
	void scale(float sx, float sy);
	void translate(float dx, float dy);

	void createBox(float scaleX, float scaleY, float rotation, float tx, float ty);

	PCPoint transform(PCPoint point);
	PCPoint deltaTransform(PCPoint point);

	static PCMatrix identityMatrix();
};

#endif

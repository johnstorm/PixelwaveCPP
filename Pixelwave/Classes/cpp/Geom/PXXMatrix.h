
#ifndef _PXX_MATRIX_H_
#define _PXX_MATRIX_H_

#include "PXXObject.h"

class PXXPoint;

class PXXMatrix : public PXXObject
{
public:
	float a;
	float b;
	float c;
	float d;
	float tx;
	float ty;

	PXXMatrix();
	PXXMatrix(float a, float b, float c, float d, float tx, float ty);
	PXXMatrix(PXXMatrix * matrix);

	void set(float a, float b, float c, float d, float tx, float ty);

	void concat(PXXMatrix matrix);
	void identity();
	void invert();
	void rotate(float angle);
	void scale(float sx, float sy);
	void translate(float dx, float dy);

	void createBox(float scaleX, float scaleY, float rotation, float tx, float ty);

	PXXPoint transform(PXXPoint point);
	PXXPoint deltaTransform(PXXPoint point);

	static PXXMatrix identityMatrix();
};

#endif

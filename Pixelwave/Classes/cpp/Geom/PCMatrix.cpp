
#include "PCMatrix.h"

#include "PCPoint.h"

PCMatrix::PCMatrix()
{
	this->identity();
}
PCMatrix::PCMatrix(float a, float b, float c, float d, float tx, float ty)
{
	this->set(a, b, c, d, tx, ty);
}
PCMatrix::PCMatrix(PCMatrix * matrix)
{
	if (matrix != NULL)
	{
		this->set(matrix->a, matrix->b, matrix->c, matrix->d, matrix->tx, matrix->ty);
	}
}

void PCMatrix::set(float a, float b, float c, float d, float tx, float ty)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->tx = tx;
	this->ty = ty;
}

void PCMatrix::concat(PCMatrix matrix)
{
	float a2 = a;
	float b2 = b;
	float c2 = c;
	float d2 = d;
	float tx2 = tx;
	float ty2 = ty;

	float a1 = matrix.a;
	float b1 = matrix.b;
	float c1 = matrix.c;
	float d1 = matrix.d;
	float tx1 = matrix.tx;
	float ty1 = matrix.ty;

	a = a1 * a2 + b1 * c2;
	b = a1 * b2 + b1 * d2;
	c = c1 * a2 + d1 * c2;
	d = c1 * b2 + d1 * d2;

	tx = tx1 * a2 + ty1 * c2 + tx2;
	ty = tx1 * b2 + ty1 * d2 + ty2;
}

void PCMatrix::identity()
{
	this->set(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
}

void PCMatrix::invert()
{
	float oldA = a;
	float oldB = b;
	float oldC = c;
	float oldD = d;
	float oldTX = tx;
	float oldTY = ty;

	float denom = (oldA * oldD - oldB * oldC);

	if (PCMathIsZero(denom))
	{
		this->identity();
		return;
	}

	float invBottom = 1.0f / denom;

	a  =  oldD * invBottom;
	b  = -oldB * invBottom;
	c  = -oldC * invBottom;
	d  =  oldA * invBottom;
	tx = (oldC * oldTY - oldD * oldTX)  * invBottom;
	ty = -(oldA * oldTY - oldB * oldTX) * invBottom;
}

void PCMatrix::rotate(float angle)
{
	float sinVal = sinf(angle);
	float cosVal = cosf(angle);

	float oldA = a;
	float oldB = b;
	float oldC = c;
	float oldD = d;
	float oldTX = tx;
	float oldTY = ty;

	a = oldA * cosVal - oldB * sinVal;
	b = oldA * sinVal + oldB * cosVal;
	c = oldC * cosVal - oldD * sinVal;
	d = oldC * sinVal + oldD * cosVal;
	tx = oldTX * cosVal - oldTY * sinVal;
	ty = oldTX * sinVal + oldTY * cosVal;
}

void PCMatrix::scale(float sx, float sy)
{
	a *= sx;
	d *= sy;
	tx *= sx;
	ty *= sy;
}

void PCMatrix::translate(float dx, float dy)
{
	tx += dx;
	ty += dy;
}

void PCMatrix::createBox(float scaleX, float scaleY, float rotation, float tx, float ty)
{
	this->identity();
	this->rotate(rotation);
	this->scale(scaleX, scaleY);
	this->translate(tx, ty);
}

PCPoint PCMatrix::transform(PCPoint point)
{
	return PCPoint(point.x * a + point.y * c + tx, point.x * b + point.y * d + ty);
}

PCPoint PCMatrix::deltaTransform(PCPoint point)
{
	return PCPoint(point.x * a + point.y * c, point.x * b + point.y * d);
}

PCMatrix PCMatrix::identityMatrix()
{
	return PCMatrix();
}

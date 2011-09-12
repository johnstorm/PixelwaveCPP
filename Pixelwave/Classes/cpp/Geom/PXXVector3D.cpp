
#include "PXXVector3D.h"

PXXVector3D::PXXVector3D()
{
	this->set(0.0f, 0.0f, 0.0f, 0.0f);
}

PXXVector3D::PXXVector3D(float x, float y, float z)
{
	this->set(x, y, z);
}

PXXVector3D::PXXVector3D(float w, float x, float y, float z)
{
	this->set(w, x, y, z);
}

PXXVector3D::PXXVector3D(PXXVector3D * vector)
{
	if (vector != NULL)
	{
		this->set(vector->w, vector->x, vector->y, vector->z);
	}
}

void PXXVector3D::set(float x, float y, float z)
{
	this->set(0.0f, x, y, z);
}

void PXXVector3D::set(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

float PXXVector3D::length()
{
	return sqrtf(this->lengthSquared());
}

float PXXVector3D::lengthSquared()
{
	return ((x * x) + (y * y) + (z * z));
}

PXXVector3D PXXVector3D::add(PXXVector3D vector)
{
	return PXXVector3D(vector.x + x, vector.y + y, vector.z + z);
}

PXXVector3D PXXVector3D::subtract(PXXVector3D vector)
{
	return PXXVector3D(vector.x - x, vector.y - y, vector.z - z);
}

PXXVector3D PXXVector3D::cross(PXXVector3D vector)
{
	return PXXVector3D((y * vector.z) - (z * vector.y),
					  (z * vector.x) - (x * vector.z),
					  (x * vector.y) - (y * vector.x));
}

void PXXVector3D::increment(PXXVector3D vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

void PXXVector3D::decrement(PXXVector3D vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
}

bool PXXVector3D::isEqual(PXXVector3D vector, bool allFour)
{
	if ((PXXMathIsEqual(x, vector.x)) && (PXXMathIsEqual(y, vector.y)) && (PXXMathIsEqual(z, vector.z)))
	{
		if (allFour == true)
		{
			if (PXXMathIsEqual(w, vector.w))
				return true;
		}
		else
			return true;
	}

	return false;
}

bool PXXVector3D::isNearlyEqual(PXXVector3D vector, float tolerance, bool allFour)
{
	if ((PXXMathIsNearlyEqual(x, vector.x, tolerance)) & (PXXMathIsNearlyEqual(y, vector.y, tolerance)) & (PXXMathIsNearlyEqual(z, vector.z, tolerance)))
	{
		if (allFour == true)
		{
			if (PXXMathIsNearlyEqual(w, vector.w, tolerance))
				return true;
		}
		else
			return true;
	}

	return false;
}

float PXXVector3D::dot(PXXVector3D vector)
{
	return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

void PXXVector3D::negate()
{
	x = -x;
	y = -y;
	z = -z;
}

float PXXVector3D::normalize()
{
	float length = this->length();

	if (PXXMathIsZero(length) == false)
	{
		float one_length = 1.0f / length;

		x *= one_length;
		y *= one_length;
		z *= one_length;
	}

	return length;
}

void PXXVector3D::project()
{
	if (PXXMathIsZero(w) == false)
	{
		float one_w = 1.0f / w;

		x *= one_w;
		y *= one_w;
		z *= one_w;
	}
}

void PXXVector3D::scale(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

float PXXVector3D::angle(PXXVector3D vectorA, PXXVector3D vectorB)
{
	vectorA.normalize();
	vectorB.normalize();

	return acosf(vectorA.dot(vectorB));
}

float PXXVector3D::distance(PXXVector3D vectorA, PXXVector3D vectorB)
{
	return sqrtf(PXXVector3D::distanceSquared(vectorA, vectorB));
}

float PXXVector3D::distanceSquared(PXXVector3D vectorA, PXXVector3D vectorB)
{
	float deltaX = vectorA.x - vectorB.x;
	float deltaY = vectorA.y - vectorB.y;
	float deltaZ = vectorA.z - vectorB.z;

	return ((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
}

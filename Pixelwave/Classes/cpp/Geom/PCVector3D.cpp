
#include "PCVector3D.h"

PCVector3D::PCVector3D()
{
	this->set(0.0f, 0.0f, 0.0f, 0.0f);
}

PCVector3D::PCVector3D(float x, float y, float z)
{
	this->set(x, y, z);
}

PCVector3D::PCVector3D(float w, float x, float y, float z)
{
	this->set(w, x, y, z);
}

PCVector3D::PCVector3D(PCVector3D * vector)
{
	if (vector != NULL)
	{
		this->set(vector->w, vector->x, vector->y, vector->z);
	}
}

void PCVector3D::set(float x, float y, float z)
{
	this->set(0.0f, x, y, z);
}

void PCVector3D::set(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

float PCVector3D::length()
{
	return sqrtf(this->lengthSquared());
}

float PCVector3D::lengthSquared()
{
	return ((x * x) + (y * y) + (z * z));
}

PCVector3D PCVector3D::add(PCVector3D vector)
{
	return PCVector3D(vector.x + x, vector.y + y, vector.z + z);
}

PCVector3D PCVector3D::subtract(PCVector3D vector)
{
	return PCVector3D(vector.x - x, vector.y - y, vector.z - z);
}

PCVector3D PCVector3D::cross(PCVector3D vector)
{
	return PCVector3D((y * vector.z) - (z * vector.y),
					  (z * vector.x) - (x * vector.z),
					  (x * vector.y) - (y * vector.x));
}

void PCVector3D::increment(PCVector3D vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

void PCVector3D::decrement(PCVector3D vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
}

bool PCVector3D::isEqual(PCVector3D vector, bool allFour)
{
	if ((PCMathIsEqual(x, vector.x)) && (PCMathIsEqual(y, vector.y)) && (PCMathIsEqual(z, vector.z)))
	{
		if (allFour == true)
		{
			if (PCMathIsEqual(w, vector.w))
				return true;
		}
		else
			return true;
	}

	return false;
}

bool PCVector3D::isNearlyEqual(PCVector3D vector, float tolerance, bool allFour)
{
	if ((PCMathIsNearlyEqual(x, vector.x, tolerance)) & (PCMathIsNearlyEqual(y, vector.y, tolerance)) & (PCMathIsNearlyEqual(z, vector.z, tolerance)))
	{
		if (allFour == true)
		{
			if (PCMathIsNearlyEqual(w, vector.w, tolerance))
				return true;
		}
		else
			return true;
	}

	return false;
}

float PCVector3D::dot(PCVector3D vector)
{
	return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

void PCVector3D::negate()
{
	x = -x;
	y = -y;
	z = -z;
}

float PCVector3D::normalize()
{
	float length = this->length();

	if (PCMathIsZero(length) == false)
	{
		float one_length = 1.0f / length;

		x *= one_length;
		y *= one_length;
		z *= one_length;
	}

	return length;
}

void PCVector3D::project()
{
	if (PCMathIsZero(w) == false)
	{
		float one_w = 1.0f / w;

		x *= one_w;
		y *= one_w;
		z *= one_w;
	}
}

void PCVector3D::scale(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

float PCVector3D::angle(PCVector3D vectorA, PCVector3D vectorB)
{
	vectorA.normalize();
	vectorB.normalize();

	return acosf(vectorA.dot(vectorB));
}

float PCVector3D::distance(PCVector3D vectorA, PCVector3D vectorB)
{
	return sqrtf(PCVector3D::distanceSquared(vectorA, vectorB));
}

float PCVector3D::distanceSquared(PCVector3D vectorA, PCVector3D vectorB)
{
	float deltaX = vectorA.x - vectorB.x;
	float deltaY = vectorA.y - vectorB.y;
	float deltaZ = vectorA.z - vectorB.z;

	return ((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
}

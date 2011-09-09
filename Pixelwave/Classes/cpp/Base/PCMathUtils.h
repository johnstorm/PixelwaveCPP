
#ifndef _PC_MATH_UTILS_H_
#define _PC_MATH_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#import "PCHeaderUtils.h"

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#pragma mark -
#pragma mark Macros
#pragma mark -

static const float pcMath1_3 = 1.0f / 3.0f;
static const float pcMath2_3 = 2.0f / 3.0f;

static const float pcMathPI_180 = M_PI / 180.0f;
static const float pcMath180_PI = 180.0f / M_PI;

#define PC_SMALL_NUM 0.00001f

#define PCMathIsZero(_num_) ((_num_) <= PC_SMALL_NUM && (_num_) >= -PC_SMALL_NUM)
#define PCMathIsOne(_num_) ((_num_) <= (1.0f + PC_SMALL_NUM) && (_num_) >= (1.0f - PC_SMALL_NUM))
#define PCMathIsNearlyEqual(_num1_, _num2_, _tol_) ((_num1_) <= ((_num2_) + _tol_) && (_num1_) >= ((_num2_) - _tol_))
#define PCMathIsEqual(_num1_, _num2_) PCMathIsNearlyEqual(_num1_, _num2_, PC_SMALL_NUM)

#define PCMathToDeg(_rads_) ((_rads_) * pcMath180_PI)
#define PCMathToRad(_degs_) ((_degs_) * pcMathPI_180)

#define PCMathMin(_val1_, _val2_) (((_val1_) < (_val2_)) ? (_val1_) : (_val2_))
#define PCMathMax(_val1_, _val2_) (((_val1_) > (_val2_)) ? (_val1_) : (_val2_))
#define PCMathClamp(_val_, _minVal_, _maxVal_) ((_val_) = ((_val_) = ((_val_) < (_minVal_) ? (_minVal_) : (_val_))) > (_maxVal_) ? (_maxVal_) : (_val_))

#pragma mark -
#pragma mark Structs
#pragma mark -

typedef struct
{
	float min;
	float max;
} PCMathRange;

typedef struct
{
	float x;
	float y;
} PCMathPoint;

typedef struct
{
	PCMathPoint pointA;
	PCMathPoint pointB;
} PCMathLine;

typedef struct
{
	PCMathPoint pointA;
	PCMathPoint pointB;
	PCMathPoint pointC;
} PCMathTriangle;

typedef struct
{
	float x;
	float y;
	float z;
} PCMathPoint3D;

typedef struct
{
	PCMathPoint3D pointA;
	PCMathPoint3D pointB;
} PCMathLine3D;

typedef struct
{
	PCMathPoint3D pointA;
	PCMathPoint3D pointB;
	PCMathPoint3D pointC;
} PCMathTriangle3D;

#pragma mark -
#pragma mark Declerations
#pragma mark -

bool PCMathIsNan(float val);

float PCMathRandom();
float PCMathFloatInRange(float min, float max);
int PCMathIntInRange(int min, int max);

void PCMathSeedRandomWithTime();
void PCMathSeedRandomWithValue(unsigned value);

float PCMathLog(float val, float base);

float PCMathLerpf(float start, float end, float percent);
int32_t PCMathNextPowerOfTwo(int32_t val);
int64_t PCMathNextPowerOfTwo64(int64_t val);

PCInline PCMathRange PCMathRangeMake(float min, float max) PCAlwaysInline;

PCInline PCMathPoint PCMathPointMake(float x, float y) PCAlwaysInline;
PCInline float PCMathPointDot(PCMathPoint point1, PCMathPoint point2) PCAlwaysInline;
PCInline float PCMathPointLen(PCMathPoint point) PCAlwaysInline;
PCInline float PCMathPointLenSq(PCMathPoint point) PCAlwaysInline;
PCInline float PCMathPointDist(PCMathPoint point1, PCMathPoint point2) PCAlwaysInline;
PCInline float PCMathPointDistSq(PCMathPoint point1, PCMathPoint point2) PCAlwaysInline;
PCInline void PCMathPointNorm(PCMathPoint * point) PCAlwaysInline;
PCInline void PCMathPointSet(PCMathPoint *point, float x, float y) PCAlwaysInline;
PCInline PCMathLine PCMathLineMake(float x1, float y1, float x2, float y2) PCAlwaysInline;
PCInline void PCMathLineSet(PCMathLine *line, float x1, float y1, float x2, float y2) PCAlwaysInline;
PCInline PCMathTriangle PCMathTriangleMake(float x1, float y1, float x2, float y2, float x3, float y3) PCAlwaysInline;
PCInline void PCMathTriangleSet(PCMathTriangle *triangle, float x1, float y1, float x2, float y2, float x3, float y3) PCAlwaysInline;

PCInline PCMathPoint3D PCMathPoint3DMake(float x, float y, float z) PCAlwaysInline;
PCInline float PCMathPoint3DDot(PCMathPoint3D point1, PCMathPoint3D point2) PCAlwaysInline;
PCInline float PCMathPoint3DLen(PCMathPoint3D point) PCAlwaysInline;
PCInline float PCMathPoint3DLenSq(PCMathPoint3D point) PCAlwaysInline;
PCInline float PCMathPoint3DDist(PCMathPoint3D point1, PCMathPoint3D point2) PCAlwaysInline;
PCInline float PCMathPoint3DDistSq(PCMathPoint3D point1, PCMathPoint3D point2) PCAlwaysInline;
PCInline PCMathPoint3D PCMathPoint3DCross(PCMathPoint3D point1, PCMathPoint3D point2) PCAlwaysInline;
PCInline void PCMathPoint3DNorm(PCMathPoint3D * point) PCAlwaysInline;
PCInline void PCMathPoint3DSet(PCMathPoint3D *point, float x, float y, float z) PCAlwaysInline;
PCInline PCMathLine3D PCMathLine3DMake(float x1, float y1, float z1, float x2, float y2, float z2) PCAlwaysInline;
PCInline void PCMathLine3DSet(PCMathLine3D *line, float x1, float y1, float z1, float x2, float y2, float z2) PCAlwaysInline;
PCInline PCMathTriangle3D PCMathTriangle3DMake(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) PCAlwaysInline;
PCInline void PCMathTriangl3DeSet(PCMathTriangle3D *triangle, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) PCAlwaysInline;

float PCMathPointDistanceToLine(PCMathPoint *point, PCMathLine *line);
bool PCMathPointInLine(PCMathPoint *ans, PCMathPoint *point, PCMathLine *line);
bool PCMathIsPointInLine(PCMathPoint *point, PCMathLine *line);
bool PCMathIsPointInTriangle(PCMathPoint *point, PCMathTriangle *triangle);

#pragma mark -
#pragma mark Implementations
#pragma mark -

PCInline PCMathRange PCMathRangeMake(float min, float max)
{
	PCMathRange range;

	range.min = min;
	range.max = max;

	return range;
}

PCInline PCMathPoint PCMathPointMake(float x, float y)
{
	PCMathPoint point;

	point.x = x;
	point.y = y;

	return point;
}
PCInline float PCMathPointDot(PCMathPoint point1, PCMathPoint point2)
{
	return ((point1.x * point2.x) + (point1.y * point2.y));
}
PCInline float PCMathPointLen(PCMathPoint point)
{
	float xSq = point.x * point.x;
	float ySq = point.y * point.y;

	return sqrtf(xSq + ySq);
}
PCInline float PCMathPointLenSq(PCMathPoint point)
{
	float xSq = point.x * point.x;
	float ySq = point.y * point.y;

	return xSq + ySq;
}
PCInline float PCMathPointDist(PCMathPoint point1, PCMathPoint point2)
{
	float xSq = point2.x - point1.x;
	xSq *= xSq;
	float ySq = point2.y - point1.y;
	ySq *= ySq;

	return sqrtf(xSq + ySq);
}
PCInline float PCMathPointDistSq(PCMathPoint point1, PCMathPoint point2)
{
	float xSq = point2.x - point1.x;
	xSq *= xSq;
	float ySq = point2.y - point1.y;
	ySq *= ySq;

	return (xSq + ySq);
}
PCInline void PCMathPointNorm(PCMathPoint *point)
{
	float xSq = point->x * point->x;
	float ySq = point->y * point->y;

	float len = sqrtf(xSq + ySq);

	if (!PCMathIsZero(len))
	{
		float one_len = 1.0f / len;

		point->x *= one_len;
		point->y *= one_len;
	}
}
PCInline void PCMathPointSet(PCMathPoint *point, float x, float y)
{
	point->x = x;
	point->y = y;
}

PCInline PCMathLine PCMathLineMake(float x1, float y1,
								   float x2, float y2)
{
	PCMathLine line;

	line.pointA.x = x1;
	line.pointA.y = y1;
	line.pointB.x = x2;
	line.pointB.y = y2;

	return line;
}

PCInline void PCMathLineSet(PCMathLine *line,
							float x1, float y1,
							float x2, float y2)
{
	line->pointA.x = x1;
	line->pointA.y = y1;
	line->pointB.x = x2;
	line->pointB.y = y2;
}

PCInline PCMathTriangle PCMathTriangleMake(float x1, float y1,
												float x2, float y2,
												float x3, float y3)
{
	PCMathTriangle triangle;

	triangle.pointA.x = x1;
	triangle.pointA.y = y1;
	triangle.pointB.x = x2;
	triangle.pointB.y = y2;
	triangle.pointC.x = x3;
	triangle.pointC.y = y3;

	return triangle;
}

PCInline void PCMathTriangleSet(PCMathTriangle *triangle,
								float x1, float y1,
								float x2, float y2,
								float x3, float y3)
{
	triangle->pointA.x = x1;
	triangle->pointA.y = y1;
	triangle->pointB.x = x2;
	triangle->pointB.y = y2;
	triangle->pointC.x = x3;
	triangle->pointC.y = y3;
}

PCInline PCMathPoint3D PCMathPoint3DMake(float x, float y, float z)
{
	PCMathPoint3D point;

	point.x = x;
	point.y = y;
	point.z = z;

	return point;
}
PCInline float PCMathPoint3DDot(PCMathPoint3D point1, PCMathPoint3D point2)
{
	return ((point1.x * point2.x) + (point1.y * point2.y) + (point1.z * point2.z));
}
PCInline float PCMathPoint3DLen(PCMathPoint3D point)
{
	float xSq = point.x * point.x;
	float ySq = point.y * point.y;
	float zSq = point.z * point.z;

	return sqrtf(xSq + ySq + zSq);
}
PCInline float PCMathPoint3DLenSq(PCMathPoint3D point)
{
	float xSq = point.x * point.x;
	float ySq = point.y * point.y;
	float zSq = point.z * point.z;

	return (xSq + ySq + zSq);
}
PCInline float PCMathPoint3DDist(PCMathPoint3D point1, PCMathPoint3D point2)
{
	float xSq = point2.x - point1.x;
	xSq *= xSq;
	float ySq = point2.y - point1.y;
	ySq *= ySq;
	float zSq = point2.z - point1.z;
	zSq *= zSq;

	return sqrtf(xSq + ySq + zSq);
}
PCInline float PCMathPoint3DDistSq(PCMathPoint3D point1, PCMathPoint3D point2)
{
	float xSq = point2.x - point1.x;
	xSq *= xSq;
	float ySq = point2.y - point1.y;
	ySq *= ySq;
	float zSq = point2.z - point1.z;
	zSq *= zSq;

	return (xSq + ySq + zSq);
}
PCInline PCMathPoint3D PCMathPoint3DCross(PCMathPoint3D point1, PCMathPoint3D point2)
{
	PCMathPoint3D point;

	point.x = (point1.y * point2.z) - (point1.z * point2.y);
	point.y = (point1.z * point2.x) - (point1.x * point2.z);
	point.z = (point1.x * point2.y) - (point1.y * point2.x);

	return point;
}
PCInline void PCMathPoint3DNorm(PCMathPoint3D * point)
{
	float xSq = point->x * point->x;
	float ySq = point->y * point->y;
	float zSq = point->z * point->z;

	float len = sqrtf(xSq + ySq + zSq);

	if (!PCMathIsZero(len))
	{
		float one_len = 1.0f / len;

		point->x *= one_len;
		point->y *= one_len;
		point->z *= one_len;
	}
}
PCInline void PCMathPoint3DSet(PCMathPoint3D *point, float x, float y, float z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}
PCInline PCMathLine3D PCMathLine3DMake(float x1, float y1, float z1,
									   float x2, float y2, float z2)
{
	PCMathLine3D line;

	line.pointA.x = x1;
	line.pointA.y = y1;
	line.pointA.z = z1;

	line.pointB.x = x2;
	line.pointB.y = y2;
	line.pointB.z = z2;

	return line;
}

PCInline void PCMathLine3DSet(PCMathLine3D *line,
								   float x1, float y1, float z1,
								   float x2, float y2, float z2)
{
	line->pointA.x = x1;
	line->pointA.y = y1;
	line->pointA.z = z1;

	line->pointB.x = x2;
	line->pointB.y = y2;
	line->pointB.z = z2;
}

PCInline PCMathTriangle3D PCMathTriangle3DMake(float x1, float y1, float z1,
											   float x2, float y2, float z2,
											   float x3, float y3, float z3)
{
	PCMathTriangle3D triangle;

	triangle.pointA.x = x1;
	triangle.pointA.y = y1;
	triangle.pointA.z = z1;

	triangle.pointB.x = x2;
	triangle.pointB.y = y2;
	triangle.pointB.z = z2;

	triangle.pointC.x = x3;
	triangle.pointC.y = y3;
	triangle.pointC.z = z3;

	return triangle;
}

PCInline void PCMathTriangl3DeSet(PCMathTriangle3D *triangle,
								  float x1, float y1, float z1,
								  float x2, float y2, float z2,
								  float x3, float y3, float z3)
{
	triangle->pointA.x = x1;
	triangle->pointA.y = y1;
	triangle->pointA.z = z1;

	triangle->pointB.x = x2;
	triangle->pointB.y = y2;
	triangle->pointB.z = z2;

	triangle->pointC.x = x3;
	triangle->pointC.y = y3;
	triangle->pointC.z = z3;
}

#ifdef __cplusplus
}
#endif
	
#endif

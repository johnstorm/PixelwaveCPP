
#ifndef _PXX_MATH_UTILS_H_
#define _PXX_MATH_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#import "PXXHeaderUtils.h"

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#pragma mark -
#pragma mark Macros
#pragma mark -

static const float pxxMath1_3 = 1.0f / 3.0f;
static const float pxxMath2_3 = 2.0f / 3.0f;

static const float pxxMathPI_180 = M_PI / 180.0f;
static const float pxxMath180_PI = 180.0f / M_PI;

#define PXX_SMALL_NUM 0.00001f

#define PXXMathIsZero(_num_) ((_num_) <= PXX_SMALL_NUM && (_num_) >= -PXX_SMALL_NUM)
#define PXXMathIsOne(_num_) ((_num_) <= (1.0f + PXX_SMALL_NUM) && (_num_) >= (1.0f - PXX_SMALL_NUM))
#define PXXMathIsNearlyEqual(_num1_, _num2_, _tol_) ((_num1_) <= ((_num2_) + _tol_) && (_num1_) >= ((_num2_) - _tol_))
#define PXXMathIsEqual(_num1_, _num2_) PXXMathIsNearlyEqual(_num1_, _num2_, PXX_SMALL_NUM)

#define PXXMathToDeg(_rads_) ((_rads_) * pxxMath180_PI)
#define PXXMathToRad(_degs_) ((_degs_) * pxxMathPI_180)

#define PXXMathMin(_val1_, _val2_) (((_val1_) < (_val2_)) ? (_val1_) : (_val2_))
#define PXXMathMax(_val1_, _val2_) (((_val1_) > (_val2_)) ? (_val1_) : (_val2_))
#define PXXMathClamp(_val_, _minVal_, _maxVal_) ((_val_) = ((_val_) = ((_val_) < (_minVal_) ? (_minVal_) : (_val_))) > (_maxVal_) ? (_maxVal_) : (_val_))

#pragma mark -
#pragma mark Structs
#pragma mark -

typedef struct
{
	float min;
	float max;
} PXXMathRange;

typedef struct
{
	float x;
	float y;
} PXXMathPoint;

typedef struct
{
	PXXMathPoint pointA;
	PXXMathPoint pointB;
} PXXMathLine;

typedef struct
{
	PXXMathPoint pointA;
	PXXMathPoint pointB;
	PXXMathPoint pointC;
} PXXMathTriangle;

typedef struct
{
	float x;
	float y;
	float z;
} PXXMathPoint3D;

typedef struct
{
	PXXMathPoint3D pointA;
	PXXMathPoint3D pointB;
} PXXMathLine3D;

typedef struct
{
	PXXMathPoint3D pointA;
	PXXMathPoint3D pointB;
	PXXMathPoint3D pointC;
} PXXMathTriangle3D;

#pragma mark -
#pragma mark Declerations
#pragma mark -

bool PXXMathIsNan(float val);

float PXXMathRandom();
float PXXMathFloatInRange(float min, float max);
int PXXMathIntInRange(int min, int max);

void PXXMathSeedRandomWithTime();
void PXXMathSeedRandomWithValue(unsigned value);

float PXXMathLog(float val, float base);

float PXXMathLerpf(float start, float end, float percent);
int32_t PXXMathNextPowerOfTwo(int32_t val);
int64_t PXXMathNextPowerOfTwo64(int64_t val);

PXXInline PXXMathRange PXXMathRangeMake(float min, float max) PXXAlwaysInline;

PXXInline PXXMathPoint PXXMathPointMake(float x, float y) PXXAlwaysInline;
PXXInline float PXXMathPointDot(PXXMathPoint point1, PXXMathPoint point2) PXXAlwaysInline;
PXXInline float PXXMathPointLen(PXXMathPoint point) PXXAlwaysInline;
PXXInline float PXXMathPointLenSq(PXXMathPoint point) PXXAlwaysInline;
PXXInline float PXXMathPointDist(PXXMathPoint point1, PXXMathPoint point2) PXXAlwaysInline;
PXXInline float PXXMathPointDistSq(PXXMathPoint point1, PXXMathPoint point2) PXXAlwaysInline;
PXXInline void PXXMathPointNorm(PXXMathPoint * point) PXXAlwaysInline;
PXXInline void PXXMathPointSet(PXXMathPoint *point, float x, float y) PXXAlwaysInline;
PXXInline PXXMathLine PXXMathLineMake(float x1, float y1, float x2, float y2) PXXAlwaysInline;
PXXInline void PXXMathLineSet(PXXMathLine *line, float x1, float y1, float x2, float y2) PXXAlwaysInline;
PXXInline PXXMathTriangle PXXMathTriangleMake(float x1, float y1, float x2, float y2, float x3, float y3) PXXAlwaysInline;
PXXInline void PXXMathTriangleSet(PXXMathTriangle *triangle, float x1, float y1, float x2, float y2, float x3, float y3) PXXAlwaysInline;

PXXInline PXXMathPoint3D PXXMathPoint3DMake(float x, float y, float z) PXXAlwaysInline;
PXXInline float PXXMathPoint3DDot(PXXMathPoint3D point1, PXXMathPoint3D point2) PXXAlwaysInline;
PXXInline float PXXMathPoint3DLen(PXXMathPoint3D point) PXXAlwaysInline;
PXXInline float PXXMathPoint3DLenSq(PXXMathPoint3D point) PXXAlwaysInline;
PXXInline float PXXMathPoint3DDist(PXXMathPoint3D point1, PXXMathPoint3D point2) PXXAlwaysInline;
PXXInline float PXXMathPoint3DDistSq(PXXMathPoint3D point1, PXXMathPoint3D point2) PXXAlwaysInline;
PXXInline PXXMathPoint3D PXXMathPoint3DCross(PXXMathPoint3D point1, PXXMathPoint3D point2) PXXAlwaysInline;
PXXInline void PXXMathPoint3DNorm(PXXMathPoint3D * point) PXXAlwaysInline;
PXXInline void PXXMathPoint3DSet(PXXMathPoint3D *point, float x, float y, float z) PXXAlwaysInline;
PXXInline PXXMathLine3D PXXMathLine3DMake(float x1, float y1, float z1, float x2, float y2, float z2) PXXAlwaysInline;
PXXInline void PXXMathLine3DSet(PXXMathLine3D *line, float x1, float y1, float z1, float x2, float y2, float z2) PXXAlwaysInline;
PXXInline PXXMathTriangle3D PXXMathTriangle3DMake(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) PXXAlwaysInline;
PXXInline void PXXMathTriangl3DeSet(PXXMathTriangle3D *triangle, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) PXXAlwaysInline;

float PXXMathPointDistanceToLine(PXXMathPoint *point, PXXMathLine *line);
bool PXXMathPointInLine(PXXMathPoint *ans, PXXMathPoint *point, PXXMathLine *line);
bool PXXMathIsPointInLine(PXXMathPoint *point, PXXMathLine *line);
bool PXXMathIsPointInTriangle(PXXMathPoint *point, PXXMathTriangle *triangle);

#pragma mark -
#pragma mark Implementations
#pragma mark -

PXXInline PXXMathRange PXXMathRangeMake(float min, float max)
{
	PXXMathRange range;

	range.min = min;
	range.max = max;

	return range;
}

PXXInline PXXMathPoint PXXMathPointMake(float x, float y)
{
	PXXMathPoint point;

	point.x = x;
	point.y = y;

	return point;
}
PXXInline float PXXMathPointDot(PXXMathPoint point1, PXXMathPoint point2)
{
	return ((point1.x * point2.x) + (point1.y * point2.y));
}
PXXInline float PXXMathPointLen(PXXMathPoint point)
{
	float xSq = point.x * point.x;
	float ySq = point.y * point.y;

	return sqrtf(xSq + ySq);
}
PXXInline float PXXMathPointLenSq(PXXMathPoint point)
{
	float xSq = point.x * point.x;
	float ySq = point.y * point.y;

	return xSq + ySq;
}
PXXInline float PXXMathPointDist(PXXMathPoint point1, PXXMathPoint point2)
{
	float xSq = point2.x - point1.x;
	xSq *= xSq;
	float ySq = point2.y - point1.y;
	ySq *= ySq;

	return sqrtf(xSq + ySq);
}
PXXInline float PXXMathPointDistSq(PXXMathPoint point1, PXXMathPoint point2)
{
	float xSq = point2.x - point1.x;
	xSq *= xSq;
	float ySq = point2.y - point1.y;
	ySq *= ySq;

	return (xSq + ySq);
}
PXXInline void PXXMathPointNorm(PXXMathPoint *point)
{
	float xSq = point->x * point->x;
	float ySq = point->y * point->y;

	float len = sqrtf(xSq + ySq);

	if (!PXXMathIsZero(len))
	{
		float one_len = 1.0f / len;

		point->x *= one_len;
		point->y *= one_len;
	}
}
PXXInline void PXXMathPointSet(PXXMathPoint *point, float x, float y)
{
	point->x = x;
	point->y = y;
}

PXXInline PXXMathLine PXXMathLineMake(float x1, float y1,
								   float x2, float y2)
{
	PXXMathLine line;

	line.pointA.x = x1;
	line.pointA.y = y1;
	line.pointB.x = x2;
	line.pointB.y = y2;

	return line;
}

PXXInline void PXXMathLineSet(PXXMathLine *line,
							float x1, float y1,
							float x2, float y2)
{
	line->pointA.x = x1;
	line->pointA.y = y1;
	line->pointB.x = x2;
	line->pointB.y = y2;
}

PXXInline PXXMathTriangle PXXMathTriangleMake(float x1, float y1,
												float x2, float y2,
												float x3, float y3)
{
	PXXMathTriangle triangle;

	triangle.pointA.x = x1;
	triangle.pointA.y = y1;
	triangle.pointB.x = x2;
	triangle.pointB.y = y2;
	triangle.pointC.x = x3;
	triangle.pointC.y = y3;

	return triangle;
}

PXXInline void PXXMathTriangleSet(PXXMathTriangle *triangle,
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

PXXInline PXXMathPoint3D PXXMathPoint3DMake(float x, float y, float z)
{
	PXXMathPoint3D point;

	point.x = x;
	point.y = y;
	point.z = z;

	return point;
}
PXXInline float PXXMathPoint3DDot(PXXMathPoint3D point1, PXXMathPoint3D point2)
{
	return ((point1.x * point2.x) + (point1.y * point2.y) + (point1.z * point2.z));
}
PXXInline float PXXMathPoint3DLen(PXXMathPoint3D point)
{
	float xSq = point.x * point.x;
	float ySq = point.y * point.y;
	float zSq = point.z * point.z;

	return sqrtf(xSq + ySq + zSq);
}
PXXInline float PXXMathPoint3DLenSq(PXXMathPoint3D point)
{
	float xSq = point.x * point.x;
	float ySq = point.y * point.y;
	float zSq = point.z * point.z;

	return (xSq + ySq + zSq);
}
PXXInline float PXXMathPoint3DDist(PXXMathPoint3D point1, PXXMathPoint3D point2)
{
	float xSq = point2.x - point1.x;
	xSq *= xSq;
	float ySq = point2.y - point1.y;
	ySq *= ySq;
	float zSq = point2.z - point1.z;
	zSq *= zSq;

	return sqrtf(xSq + ySq + zSq);
}
PXXInline float PXXMathPoint3DDistSq(PXXMathPoint3D point1, PXXMathPoint3D point2)
{
	float xSq = point2.x - point1.x;
	xSq *= xSq;
	float ySq = point2.y - point1.y;
	ySq *= ySq;
	float zSq = point2.z - point1.z;
	zSq *= zSq;

	return (xSq + ySq + zSq);
}
PXXInline PXXMathPoint3D PXXMathPoint3DCross(PXXMathPoint3D point1, PXXMathPoint3D point2)
{
	PXXMathPoint3D point;

	point.x = (point1.y * point2.z) - (point1.z * point2.y);
	point.y = (point1.z * point2.x) - (point1.x * point2.z);
	point.z = (point1.x * point2.y) - (point1.y * point2.x);

	return point;
}
PXXInline void PXXMathPoint3DNorm(PXXMathPoint3D * point)
{
	float xSq = point->x * point->x;
	float ySq = point->y * point->y;
	float zSq = point->z * point->z;

	float len = sqrtf(xSq + ySq + zSq);

	if (!PXXMathIsZero(len))
	{
		float one_len = 1.0f / len;

		point->x *= one_len;
		point->y *= one_len;
		point->z *= one_len;
	}
}
PXXInline void PXXMathPoint3DSet(PXXMathPoint3D *point, float x, float y, float z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}
PXXInline PXXMathLine3D PXXMathLine3DMake(float x1, float y1, float z1,
									   float x2, float y2, float z2)
{
	PXXMathLine3D line;

	line.pointA.x = x1;
	line.pointA.y = y1;
	line.pointA.z = z1;

	line.pointB.x = x2;
	line.pointB.y = y2;
	line.pointB.z = z2;

	return line;
}

PXXInline void PXXMathLine3DSet(PXXMathLine3D *line,
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

PXXInline PXXMathTriangle3D PXXMathTriangle3DMake(float x1, float y1, float z1,
											   float x2, float y2, float z2,
											   float x3, float y3, float z3)
{
	PXXMathTriangle3D triangle;

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

PXXInline void PXXMathTriangl3DeSet(PXXMathTriangle3D *triangle,
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


#ifndef _PXX_RECTANGLE_H_
#define _PXX_RECTANGLE_H_

#include "PXXObject.h"

class PXXPoint;

class PXXRectangle : public PXXObject
{
public:
	float x;
	float y;
	float width;
	float height;

	PXXRectangle();
	PXXRectangle(float x, float y, float width, float height);
	PXXRectangle(PXXRectangle * rect);

	void set(float x, float y, float width, float height);

	void setLeft(float left);
	float left();
	void setRight(float right);
	float right();
	void setTop(float top);
	float top();
	void setBottom(float bottom);
	float bottom();

	void setSize(PXXPoint point);
	PXXPoint size();

	void setBottomLeft(PXXPoint point);
	PXXPoint bottomLeft();
	void setBottomRight(PXXPoint point);
	PXXPoint bottomRight();
	void setTopLeft(PXXPoint point);
	PXXPoint topLeft();
	void setTopRight(PXXPoint point);
	PXXPoint topRight();

	bool contains(float x, float y);
	bool contains(PXXPoint point);
	bool contains(PXXRectangle rect);
	bool isEqual(PXXRectangle rect);
	bool isEmpty();

	void inflate(float dx, float dy);
	void inflate(PXXPoint point);

	PXXRectangle standardize();

	PXXRectangle intersection(PXXRectangle toIntersect);

	bool intersects(PXXRectangle toIntersect);

	void offset(float dx, float dy);
	void offset(PXXPoint point);

	void setEmpty();

	PXXRectangle unionRectangle(PXXRectangle rect);
};

#endif

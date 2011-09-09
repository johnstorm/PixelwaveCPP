
#ifndef _PC_RECTANGLE_H_
#define _PC_RECTANGLE_H_

#include "PCObject.h"

class PCPoint;

class PCRectangle : public PCObject
{
public:
	float x;
	float y;
	float width;
	float height;

	PCRectangle();
	PCRectangle(float x, float y, float width, float height);
	PCRectangle(PCRectangle * rect);

	void set(float x, float y, float width, float height);

	void setLeft(float left);
	float left();
	void setRight(float right);
	float right();
	void setTop(float top);
	float top();
	void setBottom(float bottom);
	float bottom();

	void setSize(PCPoint point);
	PCPoint size();

	void setBottomLeft(PCPoint point);
	PCPoint bottomLeft();
	void setBottomRight(PCPoint point);
	PCPoint bottomRight();
	void setTopLeft(PCPoint point);
	PCPoint topLeft();
	void setTopRight(PCPoint point);
	PCPoint topRight();

	bool contains(float x, float y);
	bool contains(PCPoint point);
	bool contains(PCRectangle rect);
	bool isEqual(PCRectangle rect);
	bool isEmpty();

	void inflate(float dx, float dy);
	void inflate(PCPoint point);

	PCRectangle standardize();

	PCRectangle intersection(PCRectangle toIntersect);

	bool intersects(PCRectangle toIntersect);

	void offset(float dx, float dy);
	void offset(PCPoint point);

	void setEmpty();

	PCRectangle unionRectangle(PCRectangle rect);
};

#endif

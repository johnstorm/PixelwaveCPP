
#include "PXXRectangle.h"

#include "PXXPoint.h"

PXXRectangle::PXXRectangle()
{
	this->set(0.0f, 0.0f, 0.0f, 0.0f);
}

PXXRectangle::PXXRectangle(float x, float y, float width, float height)
{
	this->set(x, y, width, height);
}
PXXRectangle::PXXRectangle(PXXRectangle * rect)
{
	if (rect)
	{
		this->set(rect->x, rect->y, rect->width, rect->height);
	}
}

void PXXRectangle::set(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width  = width;
	this->height = height;
}

void PXXRectangle::setLeft(float left)
{
	float cRight = x + width;
	x = left;
	width = cRight - left;
}

float PXXRectangle::left()
{
	return x;
}

void PXXRectangle::setRight(float right)
{
	width = right - x;
}

float PXXRectangle::right()
{
	return x + width;
}

void PXXRectangle::setTop(float top)
{
	float cBottom = y + height;
	y = top;
	height = cBottom - top;
}

float PXXRectangle::top()
{
	return y;
}

void PXXRectangle::setBottom(float bottom)
{
	height = bottom - y;
}

float PXXRectangle::bottom()
{
	return y + height;
}

void PXXRectangle::setSize(PXXPoint point)
{
	width  = point.x;
	height = point.y;
}

PXXPoint PXXRectangle::size()
{
	return PXXPoint(width, height);
}

void PXXRectangle::setBottomLeft(PXXPoint point)
{
	x = point.x;
	height = point.y - y;
}

PXXPoint PXXRectangle::bottomLeft()
{
	return PXXPoint(this->left(), this->bottom());
}

void PXXRectangle::setBottomRight(PXXPoint point)
{
	width  = point.x - x;
	height = point.y - y;
}

PXXPoint PXXRectangle::bottomRight()
{
	return PXXPoint(this->right(), this->bottom());
}

void PXXRectangle::setTopLeft(PXXPoint point)
{
	x = point.x;
	y = point.y;
}

PXXPoint PXXRectangle::topLeft()
{
	return PXXPoint(this->left(), this->top());
}

void PXXRectangle::setTopRight(PXXPoint point)
{
	width  = point.x - x;
	y = point.y;
}

PXXPoint PXXRectangle::topRight()
{
	return PXXPoint(this->right(), this->top());
}

bool PXXRectangle::contains(float x, float y)
{
	return (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height);
}

bool PXXRectangle::contains(PXXPoint point)
{
	return this->contains(point.x, point.y);
}

bool PXXRectangle::contains(PXXRectangle rect)
{
	if (this->contains(rect.topLeft()) == false)
		return false;
	if (this->contains(rect.topRight()) == false)
		return false;
	if (this->contains(rect.bottomLeft()) == false)
		return false;
	if (this->contains(rect.bottomRight()) == false)
		return false;

	return true;
}

bool PXXRectangle::isEqual(PXXRectangle rect)
{
	return PXXMathIsEqual(x, rect.x) && PXXMathIsEqual(width, rect.width) && PXXMathIsEqual(y, rect.y) && PXXMathIsEqual(height, rect.height);
}

bool PXXRectangle::isEmpty()
{
	return (width <= 0.0f || height <= 0.0f);
}

void PXXRectangle::inflate(float dx, float dy)
{
	x -= dx;
	y -= dy;

	width  += dx * 2.0f;
	height += dy * 2.0f;
}
void PXXRectangle::inflate(PXXPoint point)
{
	return this->inflate(point.x, point.y);
}

PXXRectangle PXXRectangle::standardize()
{
	PXXRectangle rect = PXXRectangle(this);

	if (rect.width < 0)
	{
		rect.x += rect.width;
		rect.width = -rect.width;
	}

	if (rect.height < 0)
	{
		rect.y += rect.height;
		rect.height = -rect.height;
	}

	return rect;
}

PXXRectangle PXXRectangle::intersection(PXXRectangle toIntersect)
{
	if (this->isEmpty())
		return toIntersect;
	else if (toIntersect.isEmpty())
		return PXXRectangle(this);

	PXXRectangle r1 = this->standardize();
	PXXRectangle r2 = toIntersect.standardize();

	if (r1.x + r1.width <= r2.x ||
		r2.x + r2.width <= r1.x ||
		r1.y + r1.height <= r2.y ||
		r2.y + r2.height <= r1.y)
	{
		return PXXRectangle();
	}

	PXXRectangle rect = PXXRectangle();

	rect.x = (r1.x > r2.x ? r1.x : r2.x);
	rect.y = (r1.y > r2.y ? r1.y : r2.y);

	if (r1.x + r1.width < r2.x + r2.width)
		rect.width = r1.x + r1.width - rect.x;
	else
		rect.width = r2.x + r2.width - rect.x;

	if (r1.y + r1.height < r2.y + r2.height)
		rect.height = r1.y + r1.height - rect.y;
	else
		rect.height = r2.y + r2.height - rect.y;

	return rect;
}

bool PXXRectangle::intersects(PXXRectangle toIntersect)
{
	return this->intersection(toIntersect).isEmpty();
}

void PXXRectangle::offset(float dx, float dy)
{
	x += dx;
	y += dy;
}
void PXXRectangle::offset(PXXPoint point)
{
	this->offset(point.x, point.y);
}

void PXXRectangle::setEmpty()
{
	this->set(0.0f, 0.0f, 0.0f, 0.0f);
}

PXXRectangle PXXRectangle::unionRectangle(PXXRectangle toUnion)
{
	if (this->isEmpty())
		return toUnion;
	else if (toUnion.isEmpty())
		return PXXRectangle(this);

	PXXRectangle rect = PXXRectangle();

	PXXRectangle r1 = this->standardize();
	PXXRectangle r2 = toUnion.standardize();

	rect.x = fminf(r1.x, r2.x);
	rect.y = fminf(r1.y, r2.y);
	rect.width = fmaxf(r1.x + r1.width, r2.x + r2.width);
	rect.height = fmaxf(r1.y + r1.height, r2.y + r2.height);

	return rect;
}

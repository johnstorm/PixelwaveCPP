
#include "PCRectangle.h"

#include "PCPoint.h"

PCRectangle::PCRectangle()
{
	this->set(0.0f, 0.0f, 0.0f, 0.0f);
}

PCRectangle::PCRectangle(float x, float y, float width, float height)
{
	this->set(x, y, width, height);
}
PCRectangle::PCRectangle(PCRectangle * rect)
{
	if (rect)
	{
		this->set(rect->x, rect->y, rect->width, rect->height);
	}
}

void PCRectangle::set(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width  = width;
	this->height = height;
}

void PCRectangle::setLeft(float left)
{
	float cRight = x + width;
	x = left;
	width = cRight - left;
}

float PCRectangle::left()
{
	return x;
}

void PCRectangle::setRight(float right)
{
	width = right - x;
}

float PCRectangle::right()
{
	return x + width;
}

void PCRectangle::setTop(float top)
{
	float cBottom = y + height;
	y = top;
	height = cBottom - top;
}

float PCRectangle::top()
{
	return y;
}

void PCRectangle::setBottom(float bottom)
{
	height = bottom - y;
}

float PCRectangle::bottom()
{
	return y + height;
}

void PCRectangle::setSize(PCPoint point)
{
	width  = point.x;
	height = point.y;
}

PCPoint PCRectangle::size()
{
	return PCPoint(width, height);
}

void PCRectangle::setBottomLeft(PCPoint point)
{
	x = point.x;
	height = point.y - y;
}

PCPoint PCRectangle::bottomLeft()
{
	return PCPoint(this->left(), this->bottom());
}

void PCRectangle::setBottomRight(PCPoint point)
{
	width  = point.x - x;
	height = point.y - y;
}

PCPoint PCRectangle::bottomRight()
{
	return PCPoint(this->right(), this->bottom());
}

void PCRectangle::setTopLeft(PCPoint point)
{
	x = point.x;
	y = point.y;
}

PCPoint PCRectangle::topLeft()
{
	return PCPoint(this->left(), this->top());
}

void PCRectangle::setTopRight(PCPoint point)
{
	width  = point.x - x;
	y = point.y;
}

PCPoint PCRectangle::topRight()
{
	return PCPoint(this->right(), this->top());
}

bool PCRectangle::contains(float x, float y)
{
	return (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height);
}

bool PCRectangle::contains(PCPoint point)
{
	return this->contains(point.x, point.y);
}

bool PCRectangle::contains(PCRectangle rect)
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

bool PCRectangle::isEqual(PCRectangle rect)
{
	return PCMathIsEqual(x, rect.x) && PCMathIsEqual(width, rect.width) && PCMathIsEqual(y, rect.y) && PCMathIsEqual(height, rect.height);
}

bool PCRectangle::isEmpty()
{
	return (width <= 0.0f || height <= 0.0f);
}

void PCRectangle::inflate(float dx, float dy)
{
	x -= dx;
	y -= dy;

	width  += dx * 2.0f;
	height += dy * 2.0f;
}
void PCRectangle::inflate(PCPoint point)
{
	return this->inflate(point.x, point.y);
}

PCRectangle PCRectangle::standardize()
{
	PCRectangle rect = PCRectangle(this);

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

PCRectangle PCRectangle::intersection(PCRectangle toIntersect)
{
	if (this->isEmpty())
		return toIntersect;
	else if (toIntersect.isEmpty())
		return PCRectangle(this);

	PCRectangle r1 = this->standardize();
	PCRectangle r2 = toIntersect.standardize();

	if (r1.x + r1.width <= r2.x ||
		r2.x + r2.width <= r1.x ||
		r1.y + r1.height <= r2.y ||
		r2.y + r2.height <= r1.y)
	{
		return PCRectangle();
	}

	PCRectangle rect = PCRectangle();

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

bool PCRectangle::intersects(PCRectangle toIntersect)
{
	return this->intersection(toIntersect).isEmpty();
}

void PCRectangle::offset(float dx, float dy)
{
	x += dx;
	y += dy;
}
void PCRectangle::offset(PCPoint point)
{
	this->offset(point.x, point.y);
}

void PCRectangle::setEmpty()
{
	this->set(0.0f, 0.0f, 0.0f, 0.0f);
}

PCRectangle PCRectangle::unionRectangle(PCRectangle toUnion)
{
	if (this->isEmpty())
		return toUnion;
	else if (toUnion.isEmpty())
		return PCRectangle(this);

	PCRectangle rect = PCRectangle();

	PCRectangle r1 = this->standardize();
	PCRectangle r2 = toUnion.standardize();

	rect.x = fminf(r1.x, r2.x);
	rect.y = fminf(r1.y, r2.y);
	rect.width = fmaxf(r1.x + r1.width, r2.x + r2.width);
	rect.height = fmaxf(r1.y + r1.height, r2.y + r2.height);

	return rect;
}

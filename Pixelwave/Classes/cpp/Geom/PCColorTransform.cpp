
#include "PCColorTransform.h"
#include "PCPrivateUtils.h"

PCColorTransform::PCColorTransform()
{
	this->set(1.0f, 1.0f, 1.0f, 1.0f);
}

PCColorTransform::PCColorTransform(float red, float green, float blue, float alpha)
{
	this->set(red, green, blue, alpha);
}

PCColorTransform::PCColorTransform(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	this->set(red, green, blue, alpha);
}

PCColorTransform::PCColorTransform(PCColorTransform * colorTransform)
{
	if (colorTransform != NULL)
	{
		this->set(colorTransform->redMultiplier, colorTransform->greenMultiplier, colorTransform->blueMultiplier, colorTransform->alphaMultiplier);
	}
}

void PCColorTransform::set(float red, float green, float blue, float alpha)
{
	redMultiplier = red;
	greenMultiplier = green;
	blueMultiplier = blue;
	alphaMultiplier = alpha;
}

void PCColorTransform::set(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	redMultiplier = PC_COLOR_BYTE_TO_FLOAT(red);
	greenMultiplier = PC_COLOR_BYTE_TO_FLOAT(green);
	blueMultiplier = PC_COLOR_BYTE_TO_FLOAT(blue);
	alphaMultiplier = PC_COLOR_BYTE_TO_FLOAT(alpha);
}

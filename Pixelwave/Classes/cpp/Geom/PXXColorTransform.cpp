
#include "PXXColorTransform.h"
#include "PXXPrivateUtils.h"

PXXColorTransform::PXXColorTransform()
{
	this->set(1.0f, 1.0f, 1.0f, 1.0f);
}

PXXColorTransform::PXXColorTransform(float red, float green, float blue, float alpha)
{
	this->set(red, green, blue, alpha);
}

PXXColorTransform::PXXColorTransform(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	this->set(red, green, blue, alpha);
}

PXXColorTransform::PXXColorTransform(PXXColorTransform * colorTransform)
{
	if (colorTransform != NULL)
	{
		this->set(colorTransform->redMultiplier, colorTransform->greenMultiplier, colorTransform->blueMultiplier, colorTransform->alphaMultiplier);
	}
}

void PXXColorTransform::set(float red, float green, float blue, float alpha)
{
	redMultiplier = red;
	greenMultiplier = green;
	blueMultiplier = blue;
	alphaMultiplier = alpha;
}

void PXXColorTransform::set(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	redMultiplier = PXX_COLOR_BYTE_TO_FLOAT(red);
	greenMultiplier = PXX_COLOR_BYTE_TO_FLOAT(green);
	blueMultiplier = PXX_COLOR_BYTE_TO_FLOAT(blue);
	alphaMultiplier = PXX_COLOR_BYTE_TO_FLOAT(alpha);
}


#ifndef _PXX_COLOR_TRANSFORM_H_
#define _PXX_COLOR_TRANSFORM_H_

#include "PXXObject.h"

class PXXColorTransform : public PXXObject
{
public:
	float redMultiplier;
	float greenMultiplier;
	float blueMultiplier;
	float alphaMultiplier;

	PXXColorTransform();
	PXXColorTransform(float red, float green, float blue, float alpha);
	PXXColorTransform(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	PXXColorTransform(PXXColorTransform * colorTransform);
	
	void set(float red, float green, float blue, float alpha);
	void set(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
};

#endif

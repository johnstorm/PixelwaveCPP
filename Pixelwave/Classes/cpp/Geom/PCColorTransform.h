
#ifndef _PC_COLOR_TRANSFORM_H_
#define _PC_COLOR_TRANSFORM_H_

#include "PCObject.h"

class PCColorTransform : public PCObject
{
public:
	float redMultiplier;
	float greenMultiplier;
	float blueMultiplier;
	float alphaMultiplier;

	PCColorTransform();
	PCColorTransform(float red, float green, float blue, float alpha);
	PCColorTransform(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	PCColorTransform(PCColorTransform * colorTransform);
	
	void set(float red, float green, float blue, float alpha);
	void set(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
};

#endif

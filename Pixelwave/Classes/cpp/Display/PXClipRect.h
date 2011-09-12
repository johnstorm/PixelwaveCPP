
#ifndef _PXX_POINT_H_
#define _PXX_POINT_H_

#include "PXXObject.h"

class PXXClipRect : public PXXObject
{
public:
	float x;
	float y;
	float width;
	float height;

	PXXPoint();
	PXXPoint(float x, float y);
	PXXPoint(PXXPoint * point);

	void set(float x, float y);

	float length();

	PXXPoint add(PXXPoint point);
	PXXPoint subtract(PXXPoint point);

	bool isEqual(PXXPoint point);
	void normalize();
	void normalize(float length);
	void offset(float dx, float dy);

	static float distance(PXXPoint pointA, PXXPoint pointB);
	static float angle(PXXPoint pointA, PXXPoint pointB);
	static PXXPoint interpolate(PXXPoint pointA, PXXPoint pointB, float coefficient);
	static PXXPoint polar(float len, float angle);

	static int compareX(const void *elm1, const void *elm2);
	static int compareY(const void *elm1, const void *elm2);
};

#endif


/**
 * Describes the clip area within a TextureData object. The coordinates are
 * in points as opposed to pixels.
 */
@interface PXClipRect : NSObject <NSCopying>
{
@private
	float x;
	float y;
	float width;
	float height;

	BOOL invalidated;
@public
	// Raw data
	int _numVertices;
	PXGLTextureVertex *_vertices;

	// The size of the frame within the texture atlas
	float _contentWidth, _contentHeight;
	float _contentRotation;
}

////////////////
// Properties //
////////////////

// General clip shape

/**
 * Specifies the rotation offset to be applied to the area of the texture
 * covered by this clip rect when applied to a #PXTexture.
 *
 * Rotation value is in degrees.
 *
 * @warning Avoid using values that aren't multiples of 90.0
 * (it makes the hit-test act unintuitively, albeit correctly). For regular rotation changes
 * just use the [PXTexture rotation] property.
 */
@property (nonatomic) float rotation;

// Rect specific

/**
 * The horizontal position of the top-left corner of the
 * clip rectangle, in points.
 */
@property (nonatomic) float x;
/**
 * The vertical position of the top-left corner of the
 * clip rectangle, in points.
 */
@property (nonatomic) float y;
/**
 * The width of the rectangle in points.
 */
@property (nonatomic) float width;
/**
 * The height of the rectangle in points.
 */
@property (nonatomic) float height;

/////////////
// Methods //
/////////////

// When making a version of this method without rotation, the compiler freaks
// out because it can't tell the difference between it and the similarly named
// method in PXRectangle.
- (id) initWithX:(float)x y:(float)y width:(float)width height:(float)height rotation:(float)rotation;

- (void) setX:(float)x
			y:(float)y
		width:(float)width
	   height:(float)height
	 rotation:(float)rotation;

// Utility
+ (PXClipRect *)clipRectWithX:(float)x y:(float)y width:(float)width height:(float)height;
+ (PXClipRect *)clipRectWithX:(float)x y:(float)y width:(float)width height:(float)height rotation:(float)rotation;

@end

@interface PXClipRect(PrivateButPublic)
- (void) _validate;
@end

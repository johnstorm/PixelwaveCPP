//
//  PXObject.h
//  Pixelwave
//
//  Created by Spiralstorm Games on 9/9/11.
//  Copyright 2011 Spiralstorm Games. All rights reserved.
//

#define _pxToPXX(_type_, _obj_) ((_type_)((_obj_)->pxx))

@protocol PXObject <NSObject>
@required;
- (void) _makePXX;
@end

@interface PXObject : NSObject<PXObject>
{
@public
	void *pxx;
}

@end

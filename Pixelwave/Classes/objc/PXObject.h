//
//  PXObject.h
//  Pixelwave
//
//  Created by Spiralstorm Games on 9/9/11.
//  Copyright 2011 Spiralstorm Games. All rights reserved.
//

#define _objToPCO(_type_, _obj_) ((_type_)((_obj_)->pxo))

@protocol PXObject <NSObject>
@required;
- (void) _makePXO;
@end

@interface PXObject : NSObject<PXObject>
{
@public
	void *pxo;
}

@end

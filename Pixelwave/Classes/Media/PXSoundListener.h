/*
 *  _____                       ___                                            
 * /\  _ `\  __                /\_ \                                           
 * \ \ \L\ \/\_\   __  _    ___\//\ \    __  __  __    ___     __  __    ___   
 *  \ \  __/\/\ \ /\ \/ \  / __`\\ \ \  /\ \/\ \/\ \  / __`\  /\ \/\ \  / __`\ 
 *   \ \ \/  \ \ \\/>  </ /\  __/ \_\ \_\ \ \_/ \_/ \/\ \L\ \_\ \ \_/ |/\  __/ 
 *    \ \_\   \ \_\/\_/\_\\ \____\/\____\\ \___^___ /\ \__/|\_\\ \___/ \ \____\
 *     \/_/    \/_/\//\/_/ \/____/\/____/ \/__//__ /  \/__/\/_/ \/__/   \/____/
 *       
 *           www.pixelwave.org + www.spiralstormgames.com
 *                            ~;   
 *                           ,/|\.           
 *                         ,/  |\ \.                 Core Team: Oz Michaeli
 *                       ,/    | |  \                           John Lattin
 *                     ,/      | |   |
 *                   ,/        |/    |
 *                 ./__________|----'  .
 *            ,(   ___.....-,~-''-----/   ,(            ,~            ,(        
 * _.-~-.,.-'`  `_.\,.',.-'`  )_.-~-./.-'`  `_._,.',.-'`  )_.-~-.,.-'`  `_._._,.
 * 
 * Copyright (c) 2011 Spiralstorm Games http://www.spiralstormgames.com
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

@class PXSoundTransform3D;
@class PXVector3D;

typedef enum
{
	PXSoundListener2DPerspective_TopDown = 0,
	PXSoundListener2DPerspective_SideView
} PXSoundListener2DPerspective;

@interface PXSoundListener : NSObject
{
/// @cond DX_IGNORE
@private
	PXSoundTransform3D *transform;
/// @endcond
}

/**
 * The sound transform.
 *
 * @b Default: [1,1]
 */
@property (nonatomic, copy) PXSoundTransform3D *transform;

/**
 * The forward facing vector.
 *
 * @b Default: [0,0,-1]
 */
@property (nonatomic, assign) PXVector3D *forward;
/**
 * The up facing vector.
 *
 * @b Default: [0,1,0]
 */
@property (nonatomic, assign) PXVector3D *up;

/**
 * The horizontal coordinate.
 *
 * @b Default: 0.0f
 */
@property (nonatomic) float x;
/**
 * The vertical coordinate.
 *
 * @b Default: 0.0f
 */
@property (nonatomic) float y;
/**
 * The depth coordinate.
 *
 * @b Default: 0.0f
 */
@property (nonatomic) float z;

/**
 * The horizontal velocity.
 *
 * @b Default: 0.0f
 */
@property (nonatomic) float velocityX;
/**
 * The vertical velocity.
 *
 * @b Default: 0.0f
 */
@property (nonatomic) float velocityY;
/**
 * The depth velocity.
 *
 * @b Default: 0.0f
 */
@property (nonatomic) float velocityZ;

/**
 * The default reference distance for
 * <code>PXSoundTransform3D</code>
 *
 * @b Default: 64.0f
 * @see PXSoundTransform3D
 */
@property (nonatomic) float defaultReferenceDistance;
/**
 * The default logarithmic exponent for
 * <code>PXSoundTransform3D</code>
 *
 * @b Default: 2.0f
 * @see PXSoundTransform3D
 */
@property (nonatomic) float defaultLogarithmicExponent;

//-- ScriptName: setRotation
//-- ScriptArg[0]: required
//-- ScriptArg[1]: PXSoundListener2DPerspective_SideView
- (void) setRotation:(float)rotation using2DPerspective:(PXSoundListener2DPerspective)perspective;

//-- ScriptName: setPosition
- (void) setPositionWithX:(float)x y:(float)y z:(float)z;
//-- ScriptName: setVelocity
- (void) setVelocityWithX:(float)x y:(float)y z:(float)z;
@end

/// @cond DX_IGNORE
@interface PXSoundListener(PrivateButPublic)
- (void) _setVolume:(float)volume;
@end
/// @endcond

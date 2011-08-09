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

#ifndef _PX_TEXTURE_DATA_PIXEL_FORMAT_H_
#define _PX_TEXTURE_DATA_PIXEL_FORMAT_H_

/**
 * @ingroup Display
 *
 * The possible pixel formats for a PXTextureData object.
 */
typedef enum
{
	//PXTextureDataPixelFormat_Automatic = 0,
	/// 8 bits for each color and alpha
	PXTextureDataPixelFormat_RGBA8888 = 1,
	/// 4 bits for each color and alpha
	PXTextureDataPixelFormat_RGBA4444,
	/// 5 bits for each color, and 1 bit for alpha
	PXTextureDataPixelFormat_RGBA5551,
	/// 5 bits for red, 6 for green, 5 for blue and 0 for alpha
	PXTextureDataPixelFormat_RGB565,
	/// 8 bits for each color and 0 for alpha
	PXTextureDataPixelFormat_RGB888,
	/// 8 bits for luminance
	PXTextureDataPixelFormat_L8,
	/// 0 bits for color, 8 bits for alpha
	PXTextureDataPixelFormat_A8,
	/// 8 bits for luminance and 8 bits for alpha
	PXTextureDataPixelFormat_LA88,
	/// PVR is a special encoding
	PXTextureDataPixelFormat_RGB_PVRTC2,
	/// PVR is a special encoding
	PXTextureDataPixelFormat_RGB_PVRTC4,
	/// PVR is a special encoding
	PXTextureDataPixelFormat_RGBA_PVRTC2,
	/// PVR is a special encoding
	PXTextureDataPixelFormat_RGBA_PVRTC4
} PXTextureDataPixelFormat;

#endif

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

#ifndef _PX_TEXTURE_FORMAT_UTILS_H_
#define _PX_TEXTURE_FORMAT_UTILS_H_

#import "PXHeaderUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark - Define
#pragma mark -

typedef struct
{
	UInt8 red;
	UInt8 green;
	UInt8 blue;
	UInt8 alpha;
} _PXTF_RGBA8888;

typedef struct
{
	UInt8 red;
	UInt8 green;
	UInt8 blue;
} _PXTF_RGB888;

typedef struct
{
	UInt8 val1;
	UInt8 val2;
} _PXTF_16;
typedef struct
{
	UInt8 luminance;
	UInt8 alpha;
} _PXTF_LA;

typedef _PXTF_RGBA8888			PXTF_RGBA_8888;
typedef _PXTF_RGB888			PXTF_RGB_888;
typedef _PXTF_16				PXTF_RGBA_4444;
typedef UInt16					PXTF_RGBA_5551;
typedef UInt16					PXTF_RGB_565;
typedef _PXTF_LA				PXTF_LA_88;
typedef UInt8					PXTF_A_8;
typedef UInt8					PXTF_L_8;

#pragma mark -
#pragma mark - Make
#pragma mark -

PXInline_h PXTF_RGBA_8888 PXTF_RGBA_8888_Make(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha);
PXInline_h PXTF_RGB_888 PXTF_RGB_888_Make(UInt8 red, UInt8 green, UInt8 blue);
PXInline_h PXTF_RGBA_4444 PXTF_RGBA_4444_Make(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha);
PXInline_h PXTF_RGBA_5551 PXTF_RGBA_5551_Make(UInt8 red, UInt8 green, UInt8 blue, BOOL alpha);
PXInline_h PXTF_RGB_565 PXTF_RGB_561_Make(UInt8 red, UInt8 green, UInt8 blue);
PXInline_h PXTF_LA_88 PXTF_LA_88_Make(UInt8 luminance, UInt8 alpha);
PXInline_h PXTF_A_8 PXTF_A_8_Make(UInt8 alpha);
PXInline_h PXTF_L_8 PXTF_L_8_Make(UInt8 luminance);

#pragma mark -
#pragma mark - To RGBA 8888
#pragma mark -

PXInline_h PXTF_RGBA_8888 PXTF_RGBA_8888_To_RGB_888(PXTF_RGB_888 val);
PXInline_h PXTF_RGBA_8888 PXTF_RGBA_8888_To_RGBA_4444(PXTF_RGBA_4444 val);
PXInline_h PXTF_RGBA_8888 PXTF_RGBA_8888_To_RGBA_5551(PXTF_RGBA_5551 val);
PXInline_h PXTF_RGBA_8888 PXTF_RGBA_8888_To_RGB_565(PXTF_RGB_565 val);
PXInline_h PXTF_RGBA_8888 PXTF_RGBA_8888_To_LA_88(PXTF_LA_88 val);
PXInline_h PXTF_RGBA_8888 PXTF_RGBA_8888_To_A_8(PXTF_A_8 val);
PXInline_h PXTF_RGBA_8888 PXTF_RGBA_8888_To_L_8(PXTF_L_8 val);

#pragma mark -
#pragma mark - To RGB 888
#pragma mark -

PXInline_h PXTF_RGB_888 PXTF_RGB_888_To_RGBA_8888(PXTF_RGBA_8888 val);
PXInline_h PXTF_RGB_888 PXTF_RGB_888_To_RGBA_4444(PXTF_RGBA_4444 val);
PXInline_h PXTF_RGB_888 PXTF_RGB_888_To_RGBA_5551(PXTF_RGBA_5551 val);
PXInline_h PXTF_RGB_888 PXTF_RGB_888_To_RGB_565(PXTF_RGB_565 val);
PXInline_h PXTF_RGB_888 PXTF_RGB_888_To_LA_88(PXTF_LA_88 val);
PXInline_h PXTF_RGB_888 PXTF_RGB_888_To_A_8(PXTF_A_8 val);
PXInline_h PXTF_RGB_888 PXTF_RGB_888_To_L_8(PXTF_L_8 val);

#pragma mark -
#pragma mark - To RGBA 4444
#pragma mark -

PXInline_h PXTF_RGBA_4444 PXTF_RGBA_4444_To_RGBA_8888(PXTF_RGBA_8888 val);
PXInline_h PXTF_RGBA_4444 PXTF_RGBA_4444_To_RGB_888(PXTF_RGB_888 val);
PXInline_h PXTF_RGBA_4444 PXTF_RGBA_4444_To_RGBA_5551(PXTF_RGBA_5551 val);
PXInline_h PXTF_RGBA_4444 PXTF_RGBA_4444_To_RGB_565(PXTF_RGB_565 val);
PXInline_h PXTF_RGBA_4444 PXTF_RGBA_4444_To_LA_88(PXTF_LA_88 val);
PXInline_h PXTF_RGBA_4444 PXTF_RGBA_4444_To_A_8(PXTF_A_8 val);
PXInline_h PXTF_RGBA_4444 PXTF_RGBA_4444_To_L_8(PXTF_L_8 val);

#pragma mark -
#pragma mark - To RGBA 5551
#pragma mark -

PXInline_h PXTF_RGBA_5551 PXTF_RGBA_5551_To_RGBA_8888(PXTF_RGBA_8888 val);
PXInline_h PXTF_RGBA_5551 PXTF_RGBA_5551_To_RGB_888(PXTF_RGB_888 val);
PXInline_h PXTF_RGBA_5551 PXTF_RGBA_5551_To_RGBA_4444(PXTF_RGBA_4444 val);
PXInline_h PXTF_RGBA_5551 PXTF_RGBA_5551_To_RGB_565(PXTF_RGB_565 val);
PXInline_h PXTF_RGBA_5551 PXTF_RGBA_5551_To_LA_88(PXTF_LA_88 val);
PXInline_h PXTF_RGBA_5551 PXTF_RGBA_5551_To_A_8(PXTF_A_8 val);
PXInline_h PXTF_RGBA_5551 PXTF_RGBA_5551_To_L_8(PXTF_L_8 val);

#pragma mark -
#pragma mark - To RGBA 565
#pragma mark -

PXInline_h PXTF_RGB_565 PXTF_RGB_565_To_RGBA_8888(PXTF_RGBA_8888 val);
PXInline_h PXTF_RGB_565 PXTF_RGB_565_To_RGB_888(PXTF_RGB_888 val);
PXInline_h PXTF_RGB_565 PXTF_RGB_565_To_RGBA_4444(PXTF_RGBA_4444 val);
PXInline_h PXTF_RGB_565 PXTF_RGB_565_To_RGBA_5551(PXTF_RGBA_5551 val);
PXInline_h PXTF_RGB_565 PXTF_RGB_565_To_LA_88(PXTF_LA_88 val);
PXInline_h PXTF_RGB_565 PXTF_RGB_565_To_A_8(PXTF_A_8 val);
PXInline_h PXTF_RGB_565 PXTF_RGB_565_To_L_8(PXTF_L_8 val);

#pragma mark -
#pragma mark - To LA 88
#pragma mark -

PXInline_h PXTF_LA_88 PXTF_LA_88_To_RGBA_8888(PXTF_RGBA_8888 val);
PXInline_h PXTF_LA_88 PXTF_LA_88_To_RGB_888(PXTF_RGB_888 val);
PXInline_h PXTF_LA_88 PXTF_LA_88_To_RGBA_4444(PXTF_RGBA_4444 val);
PXInline_h PXTF_LA_88 PXTF_LA_88_To_RGBA_5551(PXTF_RGBA_5551 val);
PXInline_h PXTF_LA_88 PXTF_LA_88_To_RGB_565(PXTF_RGB_565 val);
PXInline_h PXTF_LA_88 PXTF_LA_88_To_A_8(PXTF_A_8 val);
PXInline_h PXTF_LA_88 PXTF_LA_88_To_L_8(PXTF_L_8 val);

#pragma mark -
#pragma mark - To A 8
#pragma mark -

PXInline_h PXTF_A_8 PXTF_A_8_To_RGBA_8888(PXTF_RGBA_8888 val);
PXInline_h PXTF_A_8 PXTF_A_8_To_RGB_888(PXTF_RGB_888 val);
PXInline_h PXTF_A_8 PXTF_A_8_To_RGBA_4444(PXTF_RGBA_4444 val);
PXInline_h PXTF_A_8 PXTF_A_8_To_RGBA_5551(PXTF_RGBA_5551 val);
PXInline_h PXTF_A_8 PXTF_A_8_To_RGB_565(PXTF_RGB_565 val);
PXInline_h PXTF_A_8 PXTF_A_8_To_LA_88(PXTF_LA_88 val);
PXInline_h PXTF_A_8 PXTF_A_8_To_L_8(PXTF_L_8 val);

#pragma mark -
#pragma mark - To L 8
#pragma mark -

PXInline_h PXTF_L_8 PXTF_L_8_To_RGBA_8888(PXTF_RGBA_8888 val);
PXInline_h PXTF_L_8 PXTF_L_8_To_RGB_888(PXTF_RGB_888 val);
PXInline_h PXTF_L_8 PXTF_L_8_To_RGBA_4444(PXTF_RGBA_4444 val);
PXInline_h PXTF_L_8 PXTF_L_8_To_RGBA_5551(PXTF_RGBA_5551 val);
PXInline_h PXTF_L_8 PXTF_L_8_To_RGB_565(PXTF_RGB_565 val);
PXInline_h PXTF_L_8 PXTF_L_8_To_LA_88(PXTF_LA_88 val);
PXInline_h PXTF_L_8 PXTF_L_8_To_A_8(PXTF_A_8 val);

#ifdef __cplusplus
}
#endif

#endif
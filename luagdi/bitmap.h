#ifndef _BITMAP_H 
#define _BITMAP_H

#include "lua.h"
#include "lauxlib.h"


 /** bit_blt. \n
   * Remarks: 该函数对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境. \n
   * Parameters in lua：\n
   * 1、HDC： a handle provided by Windows CE to the device context of an object。\n
   * 2、. \n
   * sample：;\n
   */
int bit_blt(lua_State *L);

 /** create_compatible_bitmap. \n
   * Remarks: 该函数创建与指定的设备环境相关的设备兼容的位图。需要用户在不使用是，调用delete_object \n
   * Parameters in lua：\n
   * 1、HDC： a handle provided by Windows CE to the device context of an object。\n
   * 2、nLeftRect : Specifies the bitmap width, in pixels. \n
   * 3、nTopRect :  Specifies the bitmap height, in pixels.\n
   * return: HBITMAP :If the function succeeds, the return value is a handle to the bitmap ;If the function fails, the return value is NULL\n
   * sample：local mem_dc = gdi.create_compatible_bitmap(hdc,100,100);\n
   */
int create_compatible_bitmap(lua_State *L);





#endif

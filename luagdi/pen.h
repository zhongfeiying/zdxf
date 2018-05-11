#ifndef _PEN_H 
#define _PEN_H

#include "lua.h"
#include "lauxlib.h"

 /** create_pen. \n
   * Remarks: The CreatePen function creates a logical pen that has the specified style, width, and color。需要用户在不使用是，调用delete_object \n
   * Parameters in lua：\n
   * 1、fnPenStyle： Specifies the width of the pen, in logical units. If nWidth is zero, the pen is a single pixel wide, regardless of the current transformation。\n
		Value 						Meaning 
		PS_SOLID 					The pen is solid. 
		PS_DASH 					The pen is dashed. This style is valid only when the pen width is one or less in device units. 
		PS_DOT 						The pen is dotted. This style is valid only when the pen width is one or less in device units. 
		PS_DASHDOT 					The pen has alternating dashes and dots. This style is valid only when the pen width is one or less in device units. 
		PS_DASHDOTDOT 				The pen has alternating dashes and double dots. This style is valid only when the pen width is one or less in device units. 
		PS_NULL 					The pen is invisible. 
		PS_INSIDEFRAME 				The pen is solid. When this pen is used in any GDI drawing function that takes a bounding rectangle, the dimensions of the figure are shrunk so that it fits entirely in the bounding rectangle, taking into account the width of the pen. This applies only to geometric pens. 
   * 2、nWidth  : Specifies the width of the pen, in logical units. If nWidth is zero, the pen is a single pixel wide, regardless of the current transformation. \n
   * 3、crColor  :  Specifies a color reference for the pen color. To generate a COLORREF structure, use the RGB macro.\n
   * return: HPEN  :If the function succeeds,  the return value is a handle that identifies a logical pen ;If the function fails, the return value is NULL\n
   * sample：local hpen = gdi.create_pen("PS_SOLID",100,1);\n
   */
int create_pen(lua_State *L);


 /** create_solid_brush. \n
   * Remarks: The CreateSolidBrush function creates a logical brush that has the specified solid color。需要用户在不使用是，调用delete_object \n
   * Parameters in lua：\n
   * 1、crColor  :  Specifies a color reference for the pen color. To generate a COLORREF structure, use the RGB macro.\n
   * return: HBRUSH   :If the function succeeds, the return value identifies a logical brush;If the function fails, the return value is NULL\n
   * sample：local hbrush = gdi.create_solid_brush(1);\n
   */
int create_solid_brush(lua_State *L);


 /** ext_create_pen. \n
 HPEN ExtCreatePen(  DWORD dwPenStyle,      // pen style
  DWORD dwWidth,         // pen width
  CONST LOGBRUSH *lplb,  // brush attributes
  DWORD dwStyleCount,    // length of custom style array
  CONST DWORD *lpStyle   // custom style array);
   */
int ext_create_pen(lua_State *L);




#endif

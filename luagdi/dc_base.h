#ifndef _DC_BASE_H 
#define _DC_BASE_H

#include "lua.h"
#include "lauxlib.h"


struct Pen_Info_
{
	int r;
	int g;
	int b;
	int line_style;
	int line_width;	
}; 

typedef struct Pen_Info_ Pen_Info;
 /** get line style. \n
   * line_style = 1 : PS_DASH；=2 :PS_DOT ；else : PS_SOLID. \n
   */
int get_line_style(int line_style);
int get_pen_style(const char* pen_style);


int create_compatible_dc(lua_State *L);
int create_rect_rgn(lua_State *L);
int dp_to_lp(lua_State *L);
int delete_dc(lua_State *L);
int delete_object(lua_State *L);
int get_device_caps(lua_State *L);
int get_object_a(lua_State *L);
int get_stock_object(lua_State *L);
int select_object(lua_State *L);
int set_bk_color(lua_State *L);
int set_bk_mode(lua_State *L);
int set_pixel(lua_State *L);
int set_rop2(lua_State *L);





#endif

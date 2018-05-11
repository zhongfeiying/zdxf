#include <Windows.h>
#include <Wingdi.h>
#include "dc_base.h"


int get_line_style(int line_style)
{
  if (line_style == 1)//"STROKE_DASH"
    return PS_DASH;
  else if (line_style == 2)//STROKE_DOT
    return PS_DOT;
  else
    return PS_SOLID;
}
int get_pen_style(const char* pen_style)
{
  if (strcmp(pen_style,"PS_SOLID") == 0)
    return PS_SOLID;
  else if (strcmp(pen_style,"PS_DASH") == 0)
    return PS_DASH;
  else if (strcmp(pen_style,"PS_DOT") == 0)
    return PS_DOT;
  else if (strcmp(pen_style,"PS_DASHDOT") == 0)
    return PS_DASHDOT;
  else if (strcmp(pen_style,"PS_DASHDOTDOT") == 0)
    return PS_DASHDOTDOT;
  else if (strcmp(pen_style,"PS_NULL") == 0)
    return PS_NULL;
  else if (strcmp(pen_style,"PS_INSIDEFRAME") == 0)
    return PS_INSIDEFRAME;
  else
    return PS_SOLID;
	
}

int create_compatible_dc(lua_State *L)
{
	return 0;
}

int create_rect_rgn(lua_State *L)
{
	return 0;
}



int dp_to_lp(lua_State *L)
{
	return 0;
}

int delete_dc(lua_State *L)
{
	return 0;
}

int delete_object(lua_State *L)
{
	return 0;
}



int get_device_caps(lua_State *L)
{
	return 0;
}

int get_object_a(lua_State *L)
{
	return 0;
}

int get_stock_object(lua_State *L)
{
	return 0;
}

int select_object(lua_State *L)
{
	return 0;
}

int set_bk_color(lua_State *L)
{
	return 0;
}

int set_bk_mode(lua_State *L)
{
	return 0;
}

int set_pixel(lua_State *L)
{
	return 0;
}

int set_rop2(lua_State *L)
{
	return 0;
}









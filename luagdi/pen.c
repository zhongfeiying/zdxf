#include <Windows.h>
#include <Wingdi.h>
#include "pen.h"

#include "dc_base.h"


int create_pen(lua_State *L)
{
	int fnPenStyle  = get_pen_style(luaL_checkstring(L,1));	
	int nWidth   = luaL_checkinteger(L, 2);
	int crColor    = luaL_checkinteger(L, 3);
	HPEN   pen = CreatePen(fnPenStyle,nWidth,crColor);	
	lua_pushlightuserdata(L,pen);			
	return 1;
}

int create_solid_brush(lua_State *L)
{
	int crColor    = luaL_checkinteger(L, 1);
	HBRUSH hbrush = CreateSolidBrush(crColor);	
	lua_pushlightuserdata(L,hbrush);			
	return 1;
}

int ext_create_pen(lua_State *L)
{
	return 0;
}


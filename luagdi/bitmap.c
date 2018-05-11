#include <Windows.h>
#include <Wingdi.h>
#include "bitmap.h"



int bit_blt(lua_State *L)
{
	return 0;
}

int create_compatible_bitmap(lua_State *L)
{
	HDC hdc = lua_touserdata(L,1);	
	int nWidth   = luaL_checkinteger(L, 2);
	int nHeight   = luaL_checkinteger(L, 3);
	HBITMAP  bmp = CreateCompatibleBitmap(hdc,nWidth,nHeight);	
	lua_pushlightuserdata(L,bmp);			
	return 1;
}

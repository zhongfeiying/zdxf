#include <stdio.h>
#include <string.h>

#include <Windows.h>
#include <Wingdi.h>

extern "C"{ 
#include "lua.h"
#include "lauxlib.h"
} 


static int draw_line(lua_State *L)
{
	MessageBox(NULL,"test_drawline","test",MB_OK);
	return 1;
}



static const struct  luaL_Reg mylibs[] = { 
    { "draw_line", draw_line },
    {NULL, NULL} 
}; 

extern "C"{ 

int luaopen_luadxf(lua_State* L) 
{  
    luaL_newlib(L,mylibs);
    return 1;
}

}

#include <stdio.h>
#include <string.h>

#include <Windows.h>
#include <Wingdi.h>


#include "ap_database.h"

extern "C"{ 
#include "lua.h"
#include "lauxlib.h"
} 

AP_Database db_;

static int add_line(lua_State *L)
{
	char str[30];
	luaL_checktype(L, 1, LUA_TTABLE);	 
	lua_getfield(L,-1,"x1");
	int x1 =   lua_tonumber(L, -1);  
	
	lua_getfield(L,1,"x2");//如果是table 取出它的roleid值放到栈顶 此时的栈
	int x2 =   lua_tonumber(L, -1);  
	sprintf(str, "x2 = %d", x2);	
	MessageBox(NULL,str,str,MB_OK);	


	AP_Line *ln = new AP_Line(0,0,0,500,500,0);
	db_.add(ln);
	return 1;
}

static int add_circle(lua_State *L)
{
	return 1;
}
static int add_arc(lua_State *L)
{
	return 1;
}
static int add_text(lua_State *L)
{
	return 1;
}
static int save_dxf(lua_State *L)
{
	db_.save_dxf("d:\\a.dxf");
	return 1;
}


static const struct  luaL_Reg mylibs[] = { 
    { "add_line", add_line },
    { "add_circle", add_circle },
    { "add_arc", add_arc },
    { "add_text", add_text },
    { "save_dxf", save_dxf },
    {NULL, NULL} 
}; 

extern "C"{ 

int luaopen_apdraw(lua_State* L) 
{  
    luaL_newlib(L,mylibs);
    return 1;
}

}

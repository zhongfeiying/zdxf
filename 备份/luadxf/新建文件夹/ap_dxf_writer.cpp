#include "ap_dxf_writer.h"

void write(char* file)
{
}
void write_line(lua_State *L)
{
	HDC hdc = lua_touserdata(L,1);	
	int start_x = luaL_checkinteger(L, 2);
	int start_y = luaL_checkinteger(L, 3);
	int end_x = luaL_checkinteger(L, 4);
	int end_y = luaL_checkinteger(L, 5);	
	
	Pen_Info info = get_pen_info(L,6);			
	
	dxf_->writeLine(
        *dw,
        DL_LineData(25.0,   // start point
                    30.0,
                    0.0,
                    100.0,   // end point
                    120.0,
                    0.0),
        DL_Attributes("mainlayer", 256, -1, "BYLAYER", 1.0));
	
	lua_pushboolean(L,res);
	return 1;
}

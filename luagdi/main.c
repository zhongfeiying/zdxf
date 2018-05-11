#include <stdio.h>
#include <string.h>

#include <Windows.h>
#include <Wingdi.h>

#include "lua.h"
#include "lauxlib.h"

//gdi function realize,include six kinds
#include "dc_base.h"
#include "draw.h"
#include "text.h"
#include "bitmap.h"
#include "font.h"
#include "pen.h"


static const struct  luaL_Reg mylibs[] = { 
    { "draw_line", draw_line },
    { "draw_arc", draw_arc },
    { "draw_ellipse", draw_ellipse },
    { "draw_angle_arc", draw_angle_arc },//start
	{ "draw_polygon", draw_polygon },
	{ "draw_rectangle", draw_rectangle },	
	{ "bit_blt", bit_blt },
    { "create_compatible_bitmap", create_compatible_bitmap },
    { "create_compatible_dc", create_compatible_dc },
    { "create_font_indirect_a", create_font_indirect_a },
    { "create_pen", create_pen },
    { "create_rect_rgn", create_rect_rgn },
    { "create_solid_brush", create_solid_brush },
    { "dp_to_lp", dp_to_lp },
    { "delete_dc", delete_dc },
    { "delete_object", delete_object },
    { "ext_create_pan", ext_create_pen },
    { "ext_text_out_a", ext_text_out_a },
    { "get_device_caps", get_device_caps },
    { "get_object_a", get_object_a },
    { "get_stock_object", get_stock_object },
    { "get_text_extent_point_32a", get_text_extent_point_32a },
    { "select_object", select_object },
    { "set_bk_color", set_bk_color },
    { "set_bk_mode", set_bk_mode },
    { "set_pixel", set_pixel },
    { "set_rop2", set_rop2 },
    { "set_text_align", set_text_align },
    { "set_text_color", set_text_color },
    { "text_out", text_out },
    {NULL, NULL} 
}; 


int luaopen_luagdi(lua_State* L) 
{  
    luaL_newlib(L,mylibs);
    return 1;
}

#ifndef _TEXT_H 
#define _TEXT_H

#include "lua.h"
#include "lauxlib.h"

int text_out(lua_State *L);
int set_text_align(lua_State *L);
int set_text_color(lua_State *L);
int ext_text_out_a(lua_State *L);
int get_text_extent_point_32a(lua_State *L);





#endif

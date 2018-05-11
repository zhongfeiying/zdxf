#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iup_op.h"

#include <lua.h>
#include <lauxlib.h>

#include "iup_object.h"


Ihandle* iuplua_checkihandle(lua_State *L, int pos)
{
  Ihandle* *ih = (Ihandle**)luaL_checkudata(L, pos, "iupHandle");

  if (!(*ih))
    luaL_argerror(L, pos, "destroyed iupHandle");

  if (!iupObjectCheck(*ih))
    luaL_argerror(L, pos, "invalid Lua object, destroyed iupHandle in C but not in Lua");

  return *ih;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <limits.h>
#include <stdarg.h>

#include <lua.h>
#include <lauxlib.h>

#include "iup_op.h"
#include "iupdraw.h"
#include "iup_drvdraw.h"
#include "iup_assert.h"
#include "iup_attrib.h"





static int iDrawGetStyle(Ihandle* ih)
{
	/*
  char* style = IupGetAttribute(ih, "DRAWSTYLE");
  if (iupStrEqualNoCase(style, "FILL"))
    return IUP_DRAW_FILL;
  else if (iupStrEqualNoCase(style, "STROKE_DASH"))
    return IUP_DRAW_STROKE_DASH;
  else if (iupStrEqualNoCase(style, "STROKE_DOT"))
    return IUP_DRAW_STROKE_DOT;
  else 
    return IUP_DRAW_STROKE;
*/
    return 1;

}


void IupDrawLine(Ihandle* ih, int x1, int y1, int x2, int y2)
{
  IdrawCanvas* dc;
  unsigned char r = 0, g = 0, b = 0;
  int style;

  iupASSERT(iupObjectCheck(ih));
  if (!iupObjectCheck(ih))
    return;

  dc = (IdrawCanvas*)iupAttribGet(ih, "_IUP_DRAW_DC");
  if (!dc)
    return;

  IupGetRGB(ih, "DRAWCOLOR", &r, &g, &b);

  style = iDrawGetStyle(ih);

  iupdrvDrawLine(dc, x1, y1, x2, y2, r, g, b, style);
}

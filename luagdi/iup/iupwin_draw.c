#include <windows.h>
#include <uxtheme.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <math.h>

#include "iup_object.h"
#include "iup_drvdraw.h"




struct _IdrawCanvas{
  Ihandle* ih;
  int w, h;

  HWND hWnd;
  int release_dc;
  HBITMAP hBitmap, hOldBitmap;
  HDC hBitmapDC, hDC;
};
/******************************************************************************
                             Base Functions
*******************************************************************************/

static int iDrawGetLineStyle(int style)
{
  if (style == 1)//"STROKE_DASH"
    return PS_DASH;
  else if (style == 2)//STROKE_DOT
    return PS_DOT;
  else
    return PS_SOLID;
}
/******************************************************************************
                             Simple Draw
*******************************************************************************/

void iupdrvDrawLine(IdrawCanvas* dc, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, int style)
{
  POINT line_poly[2];
  HPEN hPen = CreatePen(iDrawGetLineStyle(style), 1, RGB(r, g, b));
  HPEN hPenOld = SelectObject(dc->hBitmapDC, hPen);

  line_poly[0].x = x1;
  line_poly[0].y = y1;
  line_poly[1].x = x2;
  line_poly[1].y = y2;
  Polyline(dc->hBitmapDC, line_poly, 2);
  SetPixelV(dc->hBitmapDC, x2, y2, RGB(r, g, b));

  SelectObject(dc->hBitmapDC, hPenOld);
  DeleteObject(hPen);
}


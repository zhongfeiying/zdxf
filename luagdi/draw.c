#include <Windows.h>
#include <Wingdi.h>



#include "draw.h"
#include "op_base.h"




int draw_line(lua_State *L)
{
	HDC hdc = lua_touserdata(L,1);	
	int start_x = luaL_checkinteger(L, 2);
	int start_y = luaL_checkinteger(L, 3);
	int end_x = luaL_checkinteger(L, 4);
	int end_y = luaL_checkinteger(L, 5);	
	
	Pen_Info info = get_pen_info(L,6);			
	HPEN pen = CreatePen(get_line_style(info.line_style),info.line_width,RGB(info.r,info.g,info.b));
	HGDIOBJ old_pen = SelectObject(hdc,pen);
 
	MoveToEx(hdc,start_x,start_y,NULL);
	BOOL res = LineTo(hdc,end_x,end_y);
	
	DeleteObject(pen);
	SelectObject(hdc,old_pen);
	
	lua_pushboolean(L,res);
	return 1;
}


int draw_arc(lua_State *L)
{	
	HDC hdc = lua_touserdata(L,1);	
	int nLeftRect  = luaL_checkinteger(L, 2);
	int nTopRect  = luaL_checkinteger(L, 3);
	int nRightRect  = luaL_checkinteger(L, 4);
	int nBottomRect  = luaL_checkinteger(L, 5);
	int nXStartArc   = luaL_checkinteger(L, 6);
	int nYStartArc   = luaL_checkinteger(L, 7);
	int nXEndArc   = luaL_checkinteger(L, 8);
	int nYEndArc    = luaL_checkinteger(L, 9);	
	
	Pen_Info info = get_pen_info(L,10);			
	HPEN pen = CreatePen(get_line_style(info.line_style),info.line_width,RGB(info.r,info.g,info.b));
	HGDIOBJ old_pen = SelectObject(hdc,pen);
	
	BOOL res = Arc(hdc,nLeftRect,nTopRect,nRightRect,nBottomRect,nXStartArc,nYStartArc,nXEndArc,nYEndArc);
	
	DeleteObject(pen);
	SelectObject(hdc,old_pen);

	lua_pushboolean(L,res);
	return 1;
}
int draw_ellipse(lua_State *L)
{	
	HDC hdc = lua_touserdata(L,1);	
	int nLeftRect  = luaL_checkinteger(L, 2);
	int nTopRect  = luaL_checkinteger(L, 3);
	int nRightRect  = luaL_checkinteger(L, 4);
	int nBottomRect  = luaL_checkinteger(L, 5);  
	
	Pen_Info info = get_pen_info(L,6);	
	HPEN pen = CreatePen(get_line_style(info.line_style),info.line_width,RGB(info.r,info.g,info.b));
	HGDIOBJ old_pen = SelectObject(hdc,pen);

	BOOL res = Ellipse(hdc,nLeftRect,nTopRect,nRightRect,nBottomRect);

	DeleteObject(pen);
	SelectObject(hdc,old_pen);
	lua_pushboolean(L,res);
	return 1;
}
int draw_angle_arc(lua_State *L)
{
	HDC hdc = lua_touserdata(L,1);	
	int x  = luaL_checkinteger(L, 2);
	int y  = luaL_checkinteger(L, 3);
	int dwRadius   = luaL_checkinteger(L, 4);
	float eStartAngle   = luaL_checkinteger(L, 5);  
	float eSweepAngle   = luaL_checkinteger(L, 6);  
	
	Pen_Info info = get_pen_info(L,7);	
	HPEN pen = CreatePen(get_line_style(info.line_style),info.line_width,RGB(info.r,info.g,info.b));
	HGDIOBJ old_pen = SelectObject(hdc,pen);

	BOOL res = AngleArc(hdc,x,y,dwRadius,eStartAngle,eSweepAngle);

	DeleteObject(pen);
	SelectObject(hdc,old_pen);
	lua_pushboolean(L,res);
	return 1;
}


int draw_polygon(lua_State *L)
{
	return 0;
}

int draw_rectangle(lua_State *L)
{
	HDC hdc = lua_touserdata(L,1);	
	int nLeftRect  = luaL_checkinteger(L, 2);
	int nTopRect  = luaL_checkinteger(L, 3);
	int nRightRect  = luaL_checkinteger(L, 4);
	int nBottomRect  = luaL_checkinteger(L, 5);  
	
	Pen_Info info = get_pen_info(L,6);	
	HPEN pen = CreatePen(get_line_style(info.line_style),info.line_width,RGB(info.r,info.g,info.b));
	HGDIOBJ old_pen = SelectObject(hdc,pen);

	BOOL res = Rectangle(hdc,nLeftRect,nTopRect,nRightRect,nBottomRect);

	DeleteObject(pen);
	SelectObject(hdc,old_pen);
	lua_pushboolean(L,res);
	return 1;
}





































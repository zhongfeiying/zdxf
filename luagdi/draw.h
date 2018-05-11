#ifndef _DRAW_H 
#define _DRAW_H

#include "lua.h"
#include "lauxlib.h"

 /** draw line. \n
   * Parameters in lua：\n
   * 1、HDC： a handle provided by Windows CE to the device context of an object。\n
   * 2、start_x : x-coordinate of start point。\n
   * 3、start_y : x-coordinate of start point。\n
   * 4、end_x : y-coordinate of end point。\n
   * 5、end_y : y-coordinate of end point。\n
   * 6、lua table , include keys: line_style、line_width、r、g、b。line_style = 1 : PS_DASH；=2 :PS_DOT ；else : PS_SOLID。\n
   * sample：draw_line(HDC,start_x,start_y,end_x,end_y,{line_style="2",line_width="2",r="255",g="0",b="0"}); \n
   */
int draw_line(lua_State *L);

 /** draw arc. \n
   * Remarks: The Arc function draws an elliptical arc. \n
   * Parameters in lua：\n
   * 1、HDC： a handle provided by Windows CE to the device context of an object。\n
   * 2、nLeftRect : Specifies the logical x-coordinate of the upper-left corner of the bounding rectangle. \n
   * 3、nTopRect : Specifies the logical y-coordinate of the upper-left corner of the bounding rectangle.\n
   * 4、nRightRect :  Specifies the logical x-coordinate of the lower-right corner of the bounding rectangle. \n
   * 5、nBottomRect : Specifies the logical y-coordinate of the lower-right corner of the bounding rectangle. \n
   * 6、nXStartArc : Specifies the logical y-coordinate of the lower-right corner of the bounding rectangle. \n
   * 7、nYStartArc : Specifies the logical y-coordinate of the ending point of the radial line defining the starting point of the arc.\n
   * 8、nXEndArc : Specifies the logical x-coordinate of the ending point of the radial line defining the ending point of the arc. \n
   * 9、nYEndArc : Specifies the logical y-coordinate of the ending point of the radial line defining the ending point of the arc.\n
   * 10、lua table , include keys: line_style、line_width、r、g、b。line_style = 1 : PS_DASH；=2 :PS_DOT ；else : PS_SOLID。\n
   * sample：draw_arc(hdc,nLeftRect,nTopRect ,nRightRect ,nBottomRect ,nXStartArc ,nYStartArc ,nXEndArc  ,nYEndArc ,{line_style="2",line_width="2",r="255",g="0",b="255"}); \n
   */
int draw_arc(lua_State *L);

 /** draw ellipse. \n
   * Remarks: The Ellipse function draws an ellipse. \n
   * Parameters in lua：\n
   * 1、HDC： a handle provided by Windows CE to the device context of an object。\n
   * 2、nLeftRect : Specifies the logical x-coordinate of the upper-left corner of the bounding rectangle. \n
   * 3、nTopRect : Specifies the logical y-coordinate of the upper-left corner of the bounding rectangle.\n
   * 4、nRightRect :  Specifies the logical x-coordinate of the lower-right corner of the bounding rectangle. \n
   * 5、nBottomRect : Specifies the logical y-coordinate of the lower-right corner of the bounding rectangle. \n
   * 6、lua table , include keys: line_style、line_width、r、g、b。line_style = 1 : PS_DASH；=2 :PS_DOT ；else : PS_SOLID。\n
   * sample：draw_ellipse(hdc,nLeftRect ,nTopRect ,nRightRect ,nBottomRect ,{line_style="2",line_width="2",r="255",g="255",b="0"});\n
   */
int draw_ellipse(lua_State *L);

 /** draw angle_arc. \n
   * Remarks: The AngleArc function draws a line segment and an arc. \n
   * Parameters in lua：\n
   * 1、HDC： a handle provided by Windows CE to the device context of an object。\n
   * 2、X  : Specifies the logical x-coordinate of the center of the circle. \n
   * 3、Y : Specifies the logical y-coordinate of the center of the circle.\n
   * 2、dwRadius  :  Specifies the radius, in logical units, of the circle. This value must be positive. \n
   * 5、eStartAngle : Specifies the start angle, in degrees, relative to the x-axis. \n
   * 6、eSweepAngle : Specifies the sweep angle, in degrees, relative to the starting angle. \n
   * 7、lua table , include keys: line_style、line_width、r、g、b。line_style = 1 : PS_DASH；=2 :PS_DOT ；else : PS_SOLID。\n
   * draw_angle_arc(hdc,X,Y ,dwRadius,eStartAngle,eSweepAngle,{line_style="2",line_width="2",r="255",g="255",b="0"});\n
   */
int draw_angle_arc(lua_State *L);


int draw_polygon(lua_State *L);//????????????????


 /** draw rectangle. \n
   * Remarks: The Rectangle function draws a rectangle. \n
   * Parameters in lua：\n
   * 1、HDC： a handle provided by Windows CE to the device context of an object。\n
   * 2、nLeftRect : Specifies the logical x-coordinate of the upper-left corner of the bounding rectangle. \n
   * 3、nTopRect : Specifies the logical y-coordinate of the upper-left corner of the bounding rectangle.\n
   * 4、nRightRect :  Specifies the logical x-coordinate of the lower-right corner of the bounding rectangle. \n
   * 5、nBottomRect : Specifies the logical y-coordinate of the lower-right corner of the bounding rectangle. \n
   * 6、lua table , include keys: line_style、line_width、r、g、b。line_style = 1 : PS_DASH；=2 :PS_DOT ；else : PS_SOLID。\n
   * sample：draw_ellipse(hdc,nLeftRect ,nTopRect ,nRightRect ,nBottomRect ,{line_style="2",line_width="2",r="255",g="255",b="0"});\n
   */
int draw_rectangle(lua_State *L);




#endif

package.cpath = "./?53.dll;./?.dll";
package.path = "?;?.lua";


local apdraw_ = require"apdraw"

local gdi = require"luagdi"
--local dxf = require"luadxf"
--local dxf = require"luadxf"

--local db_ = require"luadraw//ap_database"

function on_paint(x,hdc)

	
	gdi.draw_line(hdc,50,50,200,120,{line_style="2",line_width="2",r="255",g="0",b="0"});	
	gdi.draw_arc(hdc,100,100,600,600,0,0,0,270,{line_style="2",line_width="2",r="255",g="0",b="255"});	
	gdi.draw_ellipse(hdc,100,200,500,500,{line_style="2",line_width="2",r="255",g="0",b="0"});
	gdi.draw_angle_arc(hdc,100,300,80,0,270,{line_style="2",line_width="2",r="255",g="0",b="0"});
	gdi.draw_rectangle(hdc,300,400,600,600,{line_style="2",line_width="2",r="255",g="0",b="0"});
	
	local mem_dc = gdi.create_compatible_bitmap(hdc,100,100);
	local hpen = gdi.create_pen("PS_SOLID",100,1);
	local hbrush = gdi.create_solid_brush(1);
	
	
	apdraw_.add_line({x1=10,y1=10,z1=10,x2=5000,y2=500,z2=0});
	apdraw_.save_dxf();
	--db_.add({x1=0,y1=0,z1=0,x2=5000,y2=500,z2=0}});
	--db_.save_dxf("d:\\test.dxf");
	
	return 1;
end



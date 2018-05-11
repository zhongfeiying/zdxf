
local dxf = require "luadxf"

function Line:write()
	dxf.write_line(self.st,self.ed,{line_type="dot",color={1,1,1,},...});	

end	

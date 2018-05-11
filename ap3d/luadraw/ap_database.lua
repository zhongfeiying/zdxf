package.cpath = "./?53.dll;./?.dll";
package.path = "?;?.lua";


local apdraw_ = require"apdraw"

local db_={};

function add(ent)
	table.insert(db_,ent);
end

function save_dxf(file)
	for k,v pairs(db_) do
		apdraw_.add_line(v);
	end
end
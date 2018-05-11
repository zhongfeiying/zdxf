#include <Windows.h>
#include <Wingdi.h>
#include "op_base.h"



Pen_Info get_pen_info(lua_State *L,int pos)
{
	Pen_Info info;
	info.r=info.g=info.b=0;
	info.line_style = 1;
	info.line_width = 1;
	
	int index = lua_gettable(L,pos);	
	
	lua_pushnil(L);  
	while(lua_next(L, -2))  
	{  
		const char * val = lua_tostring( L, -1 );		
		const char * key = lua_tostring( L, -2 );
		if(strcmp(key,"r")==0){
			info.r = atoi(val);
		}else if(strcmp(key,"g")==0){
			info.g = atoi(val);
		}else if(strcmp(key,"b")==0){
			info.b = atoi(val);
		}else if(strcmp(key,"line_style")==0){
			info.line_style = atoi(val);
		}else if(strcmp(key,"line_width")==0){
			info.line_width = atoi(val);
		}else {
			printf("get_pen_info key error! = %s\n",key); 
			
		}	
		lua_pop(L, 1);
	} 
		
	return info;
}
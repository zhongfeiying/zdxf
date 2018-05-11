#ifndef AP_SAVE_LUA_H_
#define AP_SAVE_LUA_H_


#include "ap_global.h"
#include "ap_visitor.h"
#include "ap_entity.h"


class APDRAW_EXPORT AP_Save_Lua : public AP_Visitor
{
	public:
		AP_Save_Lua() {}   
	
		void create(std::string file);
		void close();	
	private:
		void visit_line(const AP_Line &ln);
		void visit_arc(const AP_Arc &arc);
		void visit_circle(const AP_Circle &circle);
		void visit_text(const AP_Text &txt);
		
};



#endif
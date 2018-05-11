#ifndef AP_VISITOR_H_
#define AP_VISITOR_H_


#include "ap_global.h"

class AP_Line;
class AP_Arc;
class AP_Circle;
class AP_Text;

class APDRAW_EXPORT AP_Visitor
{
	public:
		AP_Visitor() {}   

	virtual void visit_line(const AP_Line &ln){;}
	virtual void visit_arc(const AP_Arc &arc){;}
	virtual void visit_circle(const AP_Circle &circle){;}
	virtual void visit_text(const AP_Text &txt){;}
		
};



#endif
#ifndef AP_SAVE_DXF_H_
#define AP_SAVE_DXF_H_


#include "ap_global.h"
#include "ap_visitor.h"
#include "ap_entity.h"

#include "DL_Dxf.h"


class APDRAW_EXPORT AP_Save_Dxf : public AP_Visitor
{
	public:
		AP_Save_Dxf() {}   
		
		void create(std::string file);
		void close();

		void save_header();
		void save_linetypes();
		void save_layers();
		void save_styles();
		void save_views();
		void save_appids();
		void save_dimstyles();
		void save_blocks();
		
		void save_entities_start();
		void save_entities_end();
		
	private:
		void visit_line(const AP_Line &ln);
		void visit_arc(const AP_Arc &arc);
		void visit_circle(const AP_Circle &circle);
		void visit_text(const AP_Text &txt);		
	private:
		DL_Dxf* dxf_;
		DL_WriterA* dw_;
		
};



#endif
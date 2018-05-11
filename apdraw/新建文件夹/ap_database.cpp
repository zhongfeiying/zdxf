#include "ap_database.h"

#include "ap_save_lua.h"
#include "ap_save_dxf.h"

AP_Database::AP_Database()
{
	
}
AP_Database::~AP_Database()
{
	clear();
}
void AP_Database::clear()
{
	for(int i=0; i<ents_.size(); i++){
		if(ents_[i]){
			delete ents_[i];
		}
	}
}
void AP_Database::add(AP_Entity* ent)
{
	if(ent)
		ents_.push_back(ent);
	
}
void AP_Database::save_lua(std::string file)
{
	AP_Save_Lua save_lua;
	save_lua.create(file);
	for(int i=0; i<ents_.size(); i++){
		if(ents_[i]){
			//ents_[i]->accept(save_lua);
		}
	}
	save_lua.close();
	
}
void AP_Database::save_dxf(std::string file)
{
	
	AP_Save_Dxf save_dxf;
	save_dxf.create(file);
	save_dxf.save_header();
	save_dxf.save_linetypes();
	save_dxf.save_layers();
	save_dxf.save_styles();
	save_dxf.save_views();
	save_dxf.save_appids();
	save_dxf.save_dimstyles();
	save_dxf.save_blocks();

	
	save_dxf.save_entities_start();
	for(int i=0; i<ents_.size(); i++){
		if(ents_[i]){
			ents_[i]->accept(save_dxf);
		}
	}
	save_dxf.save_entities_end();

	save_dxf.close();	
}

		

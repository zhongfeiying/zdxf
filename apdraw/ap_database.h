#ifndef AP_DATABASE_H_
#define AP_DATABASE_H_


#include "ap_global.h"
#include "ap_entity.h"


class APDRAW_EXPORT AP_Database
{
	public:
		AP_Database();
		~AP_Database();
	public:
		void add(AP_Entity* ent);
		
		void save_lua(std::string file);
		void save_dxf(std::string file);

		void clear();
	private:
		std::vector<AP_Entity*> ents_;
};



#endif
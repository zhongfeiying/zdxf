
#include "ap_save_dxf.h"
#include "ap_entity.h"



void AP_Save_Dxf::create(std::string file)
{
	dxf_ = new DL_Dxf();	
	DL_Codes::version exportVersion = DL_Codes::AC1015;	
    dw_ = dxf_->out(file.c_str(), exportVersion);
   
    dxf_->writeHeader(*dw_);
	
	
}
void AP_Save_Dxf::close()
{
	dw_->dxfEOF();
    dw_->close();
    delete dw_;
    delete dxf_;

	
}
void AP_Save_Dxf::save_header()
{
   dxf_->writeHeader(*dw_);
    /*
    // int variable:
    dw_->dxfString(9, "$INSUNITS");
    dw_->dxfInt(70, 4);
    // real (double, float) variable:
    dw_->dxfString(9, "$DIMEXE");
    dw_->dxfReal(40, 1.25);
    // string variable:
    dw_->dxfString(9, "$TEXTSTYLE");
    dw_->dxfString(7, "Standard");
    // vector variable:
    dw_->dxfString(9, "$LIMMIN");
    dw_->dxfReal(10, 0.0);
    dw_->dxfReal(20, 0.0);
    */
    dw_->sectionEnd();	
}

void AP_Save_Dxf::save_linetypes()
{
	dw_->sectionTables();
    dxf_->writeVPort(*dw_);

    dw_->tableLinetypes(3);
    dxf_->writeLinetype(*dw_, DL_LinetypeData("BYBLOCK", "BYBLOCK", 0, 0, 0.0));
    dxf_->writeLinetype(*dw_, DL_LinetypeData("BYLAYER", "BYLAYER", 0, 0, 0.0));
    dxf_->writeLinetype(*dw_, DL_LinetypeData("CONTINUOUS", "Continuous", 0, 0, 0.0));
    dw_->tableEnd();
	
}
void AP_Save_Dxf::save_layers()
{
   int numberOfLayers = 3;
    dw_->tableLayers(numberOfLayers);

    dxf_->writeLayer(*dw_,DL_LayerData("0", 0),
                   DL_Attributes(
                       std::string(""),      // leave empty
                       DL_Codes::black,        // default color
                       100,                  // default width
                       "CONTINUOUS", 1.0));       // default line style

    dxf_->writeLayer(*dw_,DL_LayerData("mainlayer", 0),DL_Attributes(std::string(""),DL_Codes::red,100,"CONTINUOUS", 1.0));
    dxf_->writeLayer(*dw_,DL_LayerData("anotherlayer", 0),DL_Attributes( std::string(""),DL_Codes::black,100,"CONTINUOUS", 1.0));

    dw_->tableEnd();	
}
void AP_Save_Dxf::save_styles()
{
	dw_->tableStyle(1);
    dxf_->writeStyle(*dw_, DL_StyleData("standard", 0, 2.5, 1.0, 0.0, 0, 2.5, "txt", ""));
    dw_->tableEnd();
	
}
void AP_Save_Dxf::save_views()
{
	dxf_->writeView(*dw_);
    dxf_->writeUcs(*dw_);	
}
void AP_Save_Dxf::save_appids()
{
	dw_->tableAppid(1);
	dxf_->writeAppid(*dw_, "ACAD");
	dw_->tableEnd();

}
void AP_Save_Dxf::save_dimstyles()
{
	dxf_->writeDimStyle(*dw_, 1, 1, 1, 1, 1);	
}
void AP_Save_Dxf::save_blocks()
{
	dxf_->writeBlockRecord(*dw_);
    dxf_->writeBlockRecord(*dw_, "myblock1");
    dxf_->writeBlockRecord(*dw_, "myblock2");
    dw_->tableEnd();
    dw_->sectionEnd();
    dw_->sectionBlocks();
    dxf_->writeBlock(*dw_, DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
    dxf_->writeEndBlock(*dw_, "*Model_Space");
    dxf_->writeBlock(*dw_, DL_BlockData("*Paper_Space", 0, 0.0, 0.0, 0.0));
    dxf_->writeEndBlock(*dw_, "*Paper_Space");
    dxf_->writeBlock(*dw_, DL_BlockData("*Paper_Space0", 0, 0.0, 0.0, 0.0));
    dxf_->writeEndBlock(*dw_, "*Paper_Space0");
    dxf_->writeBlock(*dw_, DL_BlockData("myblock1", 0, 0.0, 0.0, 0.0));
    // write block entities e.g. with dxf_->writeLine(), ..
    dxf_->writeEndBlock(*dw_, "myblock1");
    dxf_->writeBlock(*dw_, DL_BlockData("myblock2", 0, 0.0, 0.0, 0.0));
    // write block entities e.g. with dxf_->writeLine(), ..
    dxf_->writeEndBlock(*dw_, "myblock2");
    dw_->sectionEnd();	
}
void AP_Save_Dxf::save_entities_start()
{
	  dw_->sectionEntities();
	 
}
void AP_Save_Dxf::save_entities_end()
{
	dw_->sectionEnd();
    dxf_->writeObjects(*dw_);
	
    dxf_->writeObjectsEnd(*dw_);		
}

void AP_Save_Dxf::visit_line(const AP_Line &ln)
{
	 dxf_->writeLine(*dw_,DL_LineData(ln.x1,ln.y1,ln.z1,ln.x2,ln.y2,ln.z2),
        DL_Attributes(ln.get_attrib().get_layer(), ln.get_attrib().get_color(), ln.get_attrib().get_width(), ln.get_attrib().get_linetype(), ln.get_attrib().get_linetypeScale()));
}
void AP_Save_Dxf::visit_arc(const AP_Arc &arc)
{
	;
}
void AP_Save_Dxf::visit_circle(const AP_Circle &circle)
{
	;
}
void AP_Save_Dxf::visit_text(const AP_Text &txt)
{
	;
}




#ifndef AP_ENTITY_H_
#define AP_ENTITY_H_

#include <vector>
#include <string>

#include "ap_global.h"
#include "ap_property.h"
#include "ap_visitor.h"



/** * Point Data. */
class APDRAW_EXPORT AP_Point {
    AP_Point(double px=0.0, double py=0.0, double pz=0.0) {
        x = px;
        y = py;
        z = pz;
    }

    double x;
    double y;
    double z;
};


/** * Point Data. */
class APDRAW_EXPORT AP_Entity {
	public:
		AP_Entity() {}
		AP_Attributes get_attrib() const {return attrib_;}
		void set_attrib(const AP_Attributes &attrib){attrib_ = attrib;}
	
		virtual void accept(AP_Visitor &v)=0;
	protected:
		AP_Attributes attrib_;
};



/** * Line Data. */
class APDRAW_EXPORT AP_Line : public AP_Entity
{
 	public:
		AP_Line(double lx1, double ly1, double lz1,double lx2, double ly2, double lz2) 
		{
			x1 = lx1;
			y1 = ly1;
			z1 = lz1;

			x2 = lx2;
			y2 = ly2;
			z2 = lz2;
		}

		double x1; 
		double y1;
		double z1;

		double x2;
		double y2;
	
		double z2;
	private:
		void accept(AP_Visitor &v){v.visit_line(*this);}
};


/** * Arc Data. */
class APDRAW_EXPORT AP_Arc : public AP_Entity
{   
	public:
		AP_Arc(double acx, double acy, double acz,double aRadius,double aAngle1, double aAngle2) 
		{
			cx = acx;
			cy = acy;
			cz = acz;
			radius = aRadius;
			angle1 = aAngle1;
			angle2 = aAngle2;
		}
		double cx;/*! X Coordinate of center point. */
		double cy;    /*! Y Coordinate of center point. */
		double cz;    /*! Z Coordinate of center point. */
		double radius;    /*! Radius of arc. */
		double angle1;    /*! Startangle of arc in degrees. */
		double angle2;    /*! Endangle of arc in degrees. */
	private:
		void accept(AP_Visitor &v){v.visit_arc(*this);}

};

/** * Circle Data. */
class APDRAW_EXPORT AP_Circle : public AP_Entity
{   
	public:
		AP_Circle(double acx, double acy, double acz,double aRadius) 
		{
			cx = acx;
			cy = acy;
			cz = acz;
			radius = aRadius;
		}

		double cx;    /*! X Coordinate of center point. */
		double cy;    /*! Y Coordinate of center point. */
		double cz;    /*! Z Coordinate of center point. */   
		double radius; /*! Radius of arc. */
	private:
		void accept(AP_Visitor &v){v.visit_circle(*this);}
};



/** * Text Data. */
class APDRAW_EXPORT AP_Text : public AP_Entity
{  
	public:
		AP_Text(double ipx, double ipy, double ipz,double apx, double apy, double apz,double height, double xScaleFactor,
					int textGenerationFlags,int hJustification,int vJustification,const std::string& text,const std::string& style,double angle)
			: ipx(ipx), ipy(ipy), ipz(ipz),
			  apx(apx), apy(apy), apz(apz),
			  height(height), xScaleFactor(xScaleFactor),
			  textGenerationFlags(textGenerationFlags),
			  hJustification(hJustification),
			  vJustification(vJustification),
			  text(text),
			  style(style),
			  angle(angle) {
		}    
		double ipx;/*! X Coordinate of insertion point. */
		double ipy;    /*! Y Coordinate of insertion point. */
		double ipz;    /*! Z Coordinate of insertion point. */

		double apx;    /*! X Coordinate of alignment point. */
		double apy;    /*! Y Coordinate of alignment point. */
		double apz;    /*! Z Coordinate of alignment point. */

		double height;    /*! Text height */
		double xScaleFactor;    /*! Relative X scale factor. */
		int textGenerationFlags;    /*! 0 = default, 2 = Backwards, 4 = Upside down */

		/**     * Horizontal justification.     * 
		 * 0 = Left (default), 1 = Center, 2 = Right, 3 = Aligned, 4 = Middle, 5 = Fit
		 * For 3, 4, 5 the vertical alignment has to be 0.
		 */
		int hJustification;
		/**     * Vertical justification.      *
		 * 0 = Baseline (default), 1 = Bottom, 2 = Middle, 3= Top
		 */
		int vJustification;
		std::string text;    /*! Text string. */
		std::string style;    /*! Style (font). */
		double angle;    /*! Rotation angle of dimension text away from default orientation. */
	private:
		void accept(AP_Visitor &v){v.visit_text(*this);}

};



#endif

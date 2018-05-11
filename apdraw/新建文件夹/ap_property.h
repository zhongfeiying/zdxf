#ifndef AP_PROPERTY_H_
#define AP_PROPERTY_H_

#include "ap_global.h"



class APDRAW_EXPORT AP_Layer {   
    AP_Layer(const std::string& lName,int lFlags) {
        name = lName;
        flags = lFlags;
    }    
    std::string name;/** Layer name. */    
    int flags;/** Layer flags. (1 = frozen, 2 = frozen by default, 4 = locked) */
};


/** * Line Type Data. */
class APDRAW_EXPORT AP_Linetype {
 
    AP_Linetype(
        const std::string& name,
        const std::string& description,
        int flags,
        int numberOfDashes,
        double patternLength,
        double* pattern = NULL
        )
        : name(name),
        description(description),
        flags(flags),
        numberOfDashes(numberOfDashes),
        patternLength(patternLength),
        pattern(pattern)
    {}

    std::string name;    /** Linetype name */
    std::string description;    /** Linetype description */
    int flags;    /** Linetype flags */
    int numberOfDashes;    /** Number of dashes */
    double patternLength;    /** Pattern length */
    double* pattern;    /** Pattern */
};



/** * Text style data. */
class APDRAW_EXPORT AP_Style { 
    AP_Style(
        const std::string& name,
        int flags,
        double fixedTextHeight,
        double widthFactor,
        double obliqueAngle,
        int textGenerationFlags,
        double lastHeightUsed,
        const std::string& primaryFontFile,
        const std::string& bigFontFile
        )
        : name(name),
        flags(flags),
        fixedTextHeight(fixedTextHeight),
        widthFactor(widthFactor),
        obliqueAngle(obliqueAngle),
        textGenerationFlags(textGenerationFlags),
        lastHeightUsed(lastHeightUsed),
        primaryFontFile(primaryFontFile),
        bigFontFile(bigFontFile),
        bold(false),
        italic(false) {
    }

    bool operator==(const AP_Style& other) {
        // ignore lastHeightUsed:
        return (name==other.name &&
            flags==other.flags &&
            fixedTextHeight==other.fixedTextHeight &&
            widthFactor==other.widthFactor &&
            obliqueAngle==other.obliqueAngle &&
            textGenerationFlags==other.textGenerationFlags &&
            primaryFontFile==other.primaryFontFile &&
            bigFontFile==other.bigFontFile);
    }

    std::string name;    /** Style name */
    int flags;    /** Style flags */
    double fixedTextHeight;    /** Fixed text height or 0 for not fixed. */
    double widthFactor;    /** Width factor */
    double obliqueAngle;    /** Oblique angle */
    int textGenerationFlags;    /** Text generation flags */
    double lastHeightUsed;    /** Last height used */
    std::string primaryFontFile;    /** Primary font file name */
    std::string bigFontFile;    /** Big font file name */
	
    bool bold;
    bool italic;
};



class APDRAW_EXPORT AP_Attributes {

public:

    /**
     * Default conclassor.
     */
    AP_Attributes() :
        layer(""),
        color(0),
        color24(-1),
        width(0),
        linetype("BYLAYER"),
        linetypeScale(1.0),
        handle(-1),
        inPaperSpace(false) {
    }

    /**
     * Conclassor for DXF attributes.
     *
     * @param layer Layer name for this entity or NULL for no layer
     *              (every entity should be on a named layer!).
     * @param color Color number (0..256). 0 = BYBLOCK, 256 = BYLAYER.
     * @param width Line thickness. Defaults to zero. -1 = BYLAYER, 
     *               -2 = BYBLOCK, -3 = default width
     * @param linetype Line type name or "BYLAYER" or "BYBLOCK". Defaults
     *              to "BYLAYER"
     */
    AP_Attributes(const std::string& layer,
                  int color, int width,
                  const std::string& linetype,
                  double linetypeScale) :
        layer(layer),
        color(color),
        color24(-1),
        width(width),
        linetype(linetype),
        linetypeScale(linetypeScale),
        handle(-1),
        inPaperSpace(false) {

    }
    
    /**     * Conclassor for DXF attributes.     */
    AP_Attributes(const std::string& layer,int color, int color24, int width,const std::string& linetype,int handle=-1)  :
        layer(layer),
        color(color),
        color24(color24),
        width(width),
        linetype(linetype),
        linetypeScale(1.0),
        handle(handle),
        inPaperSpace(false) {
    }

    void set_layer(const std::string& layer) {
        this->layer = layer;
    }
    std::string get_layer() const {
        return layer;
    }

    void set_color(int color) {
        this->color = color;
    }    
    void set_color24(int color) {
        this->color24 = color;
    }

    int get_color() const {
        return color;
    }     
    int get_clor24() const {
        return color24;
    }

   
    void set_width(int width) {
        this->width = width;
    }
    int get_width() const {
        return width;
    }

    
    void set_linetype(const std::string& linetype) {
        this->linetype = linetype;
    }
    void set_linetypeScale(double linetypeScale) {
        this->linetypeScale = linetypeScale;
    }
    double get_linetypeScale() const {
        return linetypeScale;
    }

    std::string get_linetype() const {
        if (linetype.length()==0) {
            return "BYLAYER";
        } else {
            return linetype;
        }
    }
    void set_handle(int h) {
        handle = h;
    }
    int get_handle() const {
        return handle;
    }

    void set_inPaperSpace(bool on) {
        inPaperSpace = on;
    }

    bool is_inPaperSpace() {
        return inPaperSpace;
    }
private:
    std::string layer;
    int color;
    int color24;
    int width;
    std::string linetype;
    double linetypeScale;
    int handle;

    // DXF code 67 (true: entity in paper space, false: entity in model space (default):
    bool inPaperSpace;
};








#endif
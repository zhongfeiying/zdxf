 
#ifndef __IUP_DRVDRAW_H 
#define __IUP_DRVDRAW_H

#ifdef __cplusplus
extern "C"
{
#endif

struct _IdrawCanvas;
typedef struct _IdrawCanvas IdrawCanvas;

/** Draws an image.
 * x,y is at left,top corner of the image.
 * \ingroup draw */
void iupdrvDrawLine(IdrawCanvas* dc, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, int style);



#ifdef __cplusplus
}
#endif

#endif

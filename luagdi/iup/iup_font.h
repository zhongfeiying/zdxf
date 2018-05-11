#ifndef __IUPDRAW_H 
#define __IUPDRAW_H

#include "iup_object.h"

#ifdef __cplusplus
extern "C" {
#endif
///string/////////////////////////////////////////////////////
char* iupStrReturnStrf(const char* format, ...);
char* iupStrReturnStr(const char* str);
char *iupStrGetMemory(int size);
char* iupStrReturnIntInt(int i1, int i2, char sep);
char* iupStrReturnChecked(int check);
char* iupStrReturnFloat(float f);

///UNIX/////////////////////////////////////////////////////
void iupdrvGetKeyState(char* key);


///font/////////////////////////////////////////////////////
int iupGetFontInfo(const char* font, char *typeface, int *size, int *is_bold, int *is_italic, int *is_underline, int *is_strikeout);
int iupFontParseX(const char *font, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout);
int iupFontParseWin(const char *value, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout);
int iupFontParsePango(const char *font, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout);

char* iupGetDefaultFontSizeGlobalAttrib(void);
char* iupStrReturnInt(int i);
char* iupGetDefaultFontStyleGlobalAttrib(void);
char* iupGetDefaultFontFaceGlobalAttrib(void);


#ifdef __cplusplus
}
#endif

#endif

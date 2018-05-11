#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <limits.h>
#include <stdarg.h>

#include <lua.h>
#include <lauxlib.h>

#include "iup_op.h"
#include "iup_font.h"
#include "iup_drvdraw.h"
#include "iup_assert.h"
#include "iup_attrib.h"

#define IUP_FLOAT2STR "%.9f"

enum {                          /* style */
 FONT_PLAIN  = 0,
 FONT_BOLD   = 1,
 FONT_ITALIC = 2,
 FONT_UNDERLINE = 4,
 FONT_STRIKEOUT = 8
};


#define is_style_sep(_x) (_x == ' ' || _x == ',')

/* this code is shared between CD and IUP, must be updated on both libraries */
static int iFontFindStyleName(const char *name, int len, int *style)
{
#define STYLE_NUM_NAMES 21
  static struct { const char* name; int style; } style_names[STYLE_NUM_NAMES] = {
    {"Normal",         0},
    {"Oblique",        FONT_ITALIC},
    {"Italic",         FONT_ITALIC},
    {"Small-Caps",     0},
    {"Ultra-Light",    0},
    {"Light",          0},
    {"Medium",         0},
    {"Semi-Bold",      FONT_BOLD},
    {"Bold",           FONT_BOLD},
    {"Ultra-Bold",     FONT_BOLD},
    {"Heavy",          0},
    {"Ultra-Condensed",0},
    {"Extra-Condensed",0},
    {"Condensed",      0},
    {"Semi-Condensed", 0},
    {"Semi-Expanded",  0},
    {"Expanded",       0},
    {"Extra-Expanded", 0},
    {"Ultra-Expanded", 0},
    {"Underline", FONT_UNDERLINE},
    {"Strikeout", FONT_STRIKEOUT}
  };

  int i;
  for (i = 0; i < STYLE_NUM_NAMES; i++)
  {
    /* iupStrEqualPartial(style_names[i].name, name) */
    if (strncmp(style_names[i].name, name, len)==0)
    {
      *style = style_names[i].style;
      return 1;
    }
  }

  return 0;
}

static char* iupStrGetSmallMem(void)
{
#define SMALL_MAX_BUFFERS 100
#define SMALL_SIZE 80  /* maximum for iupStrReturnFloat */
  static char buffers[SMALL_MAX_BUFFERS][SMALL_SIZE];
  static int buffers_index = -1;
  char* ret_str;

  /* init buffers array */
  if (buffers_index == -1)
  {
    memset(buffers, 0, sizeof(char*)*SMALL_MAX_BUFFERS);
    buffers_index = 0;
  }

  /* always clear memory before returning a new buffer */
  memset(buffers[buffers_index], 0, SMALL_SIZE);
  ret_str = buffers[buffers_index];

  buffers_index++;
  if (buffers_index == SMALL_MAX_BUFFERS)
    buffers_index = 0;

  return ret_str;
#undef SMALL_MAX_BUFFERS
#undef SMALL_SIZE 
}
//string////////////////////////////////////////////////////

char *iupStrGetMemory(int size)
{
#define MAX_BUFFERS 50
  static char* buffers[MAX_BUFFERS];
  static int buffers_sizes[MAX_BUFFERS];
  static int buffers_index = -1;

  int i;

  if (size == -1) /* Frees memory */
  {
    buffers_index = -1;
    for (i = 0; i < MAX_BUFFERS; i++)
    {
      if (buffers[i]) 
      {
        free(buffers[i]);
        buffers[i] = NULL;
      }
      buffers_sizes[i] = 0;
    }
    return NULL;
  }
  else
  {
    char* ret_str;

    /* init buffers array */
    if (buffers_index == -1)
    {
      memset(buffers, 0, sizeof(char*)*MAX_BUFFERS);
      memset(buffers_sizes, 0, sizeof(int)*MAX_BUFFERS);
      buffers_index = 0;
    }

    /* first alocation */
    if (!(buffers[buffers_index]))
    {
      buffers_sizes[buffers_index] = size+1;
      buffers[buffers_index] = (char*)malloc(buffers_sizes[buffers_index]);
    }
    else if (buffers_sizes[buffers_index] < size+1)  /* reallocate if necessary */
    {
      buffers_sizes[buffers_index] = size+1;
      buffers[buffers_index] = (char*)realloc(buffers[buffers_index], buffers_sizes[buffers_index]);
    }

    /* always clear memory before returning a new buffer */
    memset(buffers[buffers_index], 0, buffers_sizes[buffers_index]);
    ret_str = buffers[buffers_index];

    buffers_index++;
    if (buffers_index == MAX_BUFFERS)
      buffers_index = 0;

    return ret_str;
  }
#undef MAX_BUFFERS
}

char* iupStrReturnStrf(const char* format, ...)
{
  char* str = iupStrGetMemory(1024);
  va_list arglist;
  va_start(arglist, format);
  vsnprintf(str, 1024, format, arglist);
  va_end(arglist);
  return str;
}

char* iupStrReturnStr(const char* str)
{
  if (str)
  {
    int size = (int)strlen(str)+1;
    char* ret_str = iupStrGetMemory(size);
    memcpy(ret_str, str, size);
    return ret_str;
  }
  else
    return NULL;
}

char* iupStrReturnIntInt(int i1, int i2, char sep)
{
  char* str = iupStrGetSmallMem();  /* 2*20 */
  sprintf(str, "%d%c%d", i1, sep, i2);
  return str;
}

char* iupStrReturnChecked(int check)
{
  if (check == -1)
    return "NOTDEF";
  else if (check)
    return "ON";
  else
    return "OFF";
}
char* iupStrReturnFloat(float f)
{
  char* str = iupStrGetSmallMem();  /* 80 */
  sprintf(str, IUP_FLOAT2STR, f);
  return str;
}
//UNIX////////////////////////////////////////////////////

void iupdrvGetKeyState(char* key)
{
	/*
  char keys[32];
  Display* display = (Display*)iupdrvGetDisplay();
  XModifierKeymap *modMap = XGetModifierMapping(display);
  XQueryKeymap(display, keys);

  if (xCheckModifier(modMap->modifiermap, modMap->max_keypermod, ShiftMapIndex, keys))
    key[0] = 'S';
  else
    key[0] = ' ';
  if (xCheckModifier(modMap->modifiermap, modMap->max_keypermod, ControlMapIndex, keys))
    key[1] = 'C';
  else
    key[1] = ' ';
  if (xCheckModifier(modMap->modifiermap, modMap->max_keypermod, Mod1MapIndex, keys) ||
      xCheckModifier(modMap->modifiermap, modMap->max_keypermod, Mod5MapIndex, keys))
    key[2] = 'A';
  else
    key[2] = ' ';
  if (xCheckModifier(modMap->modifiermap, modMap->max_keypermod, Mod4MapIndex, keys))
    key[3] = 'Y';
  else
    key[3] = ' ';

  key[4] = 0;

  XFreeModifiermap(modMap);
  */
}

//Font////////////////////////////////////////////////////

static const char * iFontGetStyleWord(const char *str, const char *last, int *wordlen)
{
  const char *result;
  
  while (last > str && is_style_sep(*(last - 1)))
    last--;

  result = last;
  while (result > str && !is_style_sep(*(result - 1)))
    result--;

  *wordlen = (int)(last - result);
  
  return result;
}

/* this code is shared between CD and IUP, must be updated on both libraries */
int iupFontParsePango(const char *font, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout)
{
  const char *p, *last;
  int len, wordlen, style;

  if (font[0] == '-')  /* X font, abort */
    return 0;

  len = (int)strlen(font);
  last = font + len;
  p = iFontGetStyleWord(font, last, &wordlen);

  /* Look for a size at the end of the string */
  if (wordlen != 0)
  {
    int new_size = atoi(p);
    if (new_size != 0)
    {
      *size = new_size;
      last = p;
    }
  }

  /* Now parse style words */
  style = 0;
  p = iFontGetStyleWord(font, last, &wordlen);
  while (wordlen != 0)
  {
    int new_style = 0;

    if (!iFontFindStyleName(p, wordlen, &new_style))
      break;
    else
    {
      style |= new_style;

      last = p;
      p = iFontGetStyleWord(font, last, &wordlen);
    }
  }

  *bold = 0;
  *italic = 0;
  *underline = 0;
  *strikeout = 0;

  if (style&FONT_BOLD)
    *bold = 1;
  if (style&FONT_ITALIC)
    *italic = 1;
  if (style&FONT_UNDERLINE)
    *underline = 1;
  if (style&FONT_STRIKEOUT)
    *strikeout = 1;

  /* Remainder is font family list. */

  /* Trim off trailing separators */
  while (last > font && is_style_sep(*(last - 1)))
    last--;

  /* Trim off leading separators */
  while (last > font && is_style_sep(*font))
    font++;

  if (font != last)
  {
    len = (int)(last - font);
    strncpy(typeface, font, len);
    typeface[len] = 0;
    return 1;
  }
  else
    return 0;
}



/* this code is shared between CD and IUP, must be updated on both libraries */
int iupFontParseWin(const char *value, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout)
{
  int c;

  if (value[0] == '-')  /* X font, abort */
    return 0;

  if (strstr(value, ":") == NULL)  /* check for the first separator */
    return 0;

  if (value[0] == ':')  /* check for NO typeface */
    value++;       /* skip separator */
  else
  {
    c = (int)strcspn(value, ":");      /* extract typeface */
    if (c == 0) return 0;
    strncpy(typeface, value, c);
    typeface[c] = '\0';
    value += c+1;  /* skip typeface and separator */
  }

  if (strstr(value, ":") == NULL)  /* check for the second separator */
    return 0;

  /* init style to none */
  *bold = 0;
  *italic = 0;
  *underline = 0;
  *strikeout = 0;

  if (value[0] == ':')  /* check for NO style list */
    value++;       /* skip separator */
  else
  {
    while (strlen(value)) /* extract style (bold/italic etc) */
    {
      char style[30];

      c = (int)strcspn(value, ":,");
      if (c == 0)
        break;

      strncpy(style, value, c);
      style[c] = '\0';

      if(iupStrEqual(style, "BOLD"))
        *bold = 1; 
      else if(iupStrEqual(style,"ITALIC"))
        *italic = 1; 
      else if(iupStrEqual(style,"UNDERLINE"))
        *underline = 1; 
      else if(iupStrEqual(style,"STRIKEOUT"))
        *strikeout = 1; 

      value += c; /* skip only the style */

      if(value[0] == ':')  /* end of style list */
      {
        value++;
        break;
      }

      value++;   /* skip separator */
    }
  }

  /* extract size in points */
  if (!iupStrToInt(value, size))
    return 0;

  if (size == 0)
    return 0;

  return 1;
}

/* this code is shared between CD and IUP, must be updated on both libraries */
int iupFontParseX(const char *font, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout)
{
  char style1[30], style2[30];
  char* token;
  char xfont[1024];

  if (font[0] != '-')
    return 0;

  strcpy(xfont, font+1);  /* skip first '-' */

  *bold = 0;
  *italic = 0;
  *underline = 0;
  *strikeout = 0;

  /* fndry */
  token = strtok(xfont, "-");
  if (!token) return 0;

  /* fmly */
  token = strtok(NULL, "-");
  if (!token) return 0;
  strcpy(typeface, token);

  /* wght */
  token = strtok(NULL, "-");
  if (!token) return 0;
  strcpy(style1, token);
  if (strstr("bold", style1))
    *bold = 1;

  /* slant */
  token = strtok(NULL, "-");
  if (!token) return 0;
  strcpy(style2, token);
  if (*style2 == 'i' || *style2 == 'o')
    *italic = 1;

  /* sWdth */
  token = strtok(NULL, "-");
  if (!token) return 0;
  /* adstyl */
  token = strtok(NULL, "-");
  if (!token) return 0;

  /* pxlsz */
  token = strtok(NULL, "-");
  if (!token) return 0;
  *size = -atoi(token); /* size in pixels */

  if (*size < 0)
    return 1;

  /* ptSz */
  token = strtok(NULL, "-");
  if (!token) return 0;
  *size = atoi(token)/10; /* size in deci-points */

  if (*size > 0)
    return 1;

  return 0;
}


char* iupStrReturnInt(int i)
{
  char* str = iupStrGetSmallMem();  /* 20 */
  sprintf(str, "%d", i);
  return str;
}


char* iupGetDefaultFontFaceGlobalAttrib(void)
{
  int size = 0;
  int is_bold = 0,
    is_italic = 0,
    is_underline = 0,
    is_strikeout = 0;
  char typeface[1024];

  char* font = IupGetGlobal("DEFAULTFONT");

  if (!iupGetFontInfo(font, typeface, &size, &is_bold, &is_italic, &is_underline, &is_strikeout))
    return NULL;

  return iupStrReturnStr(typeface);
}
char* iupGetDefaultFontStyleGlobalAttrib(void)
{
  int size = 0;
  int is_bold = 0,
    is_italic = 0,
    is_underline = 0,
    is_strikeout = 0;
  char typeface[1024];

  char* font = IupGetGlobal("DEFAULTFONT");

  if (!iupGetFontInfo(font, typeface, &size, &is_bold, &is_italic, &is_underline, &is_strikeout))
    return NULL;

  return iupStrReturnStrf("%s%s%s%s", is_bold ? "Bold " : "", is_italic ? "Italic " : "", is_underline ? "Underline " : "", is_strikeout ? "Strikeout " : "");
}

int iupGetFontInfo(const char* font, char *typeface, int *size, int *is_bold, int *is_italic, int *is_underline, int *is_strikeout)
{
  if (size) *size = 0;
  if (is_bold) *is_bold = 0;
  if (is_italic) *is_italic = 0; 
  if (is_underline) *is_underline = 0;
  if (is_strikeout) *is_strikeout = 0;
  if (typeface) *typeface = 0;
  
  /* parse the old Windows format first */
  if (!iupFontParseWin(font, typeface, size, is_bold, is_italic, is_underline, is_strikeout))
  {
    if (!iupFontParseX(font, typeface, size, is_bold, is_italic, is_underline, is_strikeout))
    {
      if (!iupFontParsePango(font, typeface, size, is_bold, is_italic, is_underline, is_strikeout))
        return 0;
    }
  }

  return 1;
}

char* iupGetDefaultFontSizeGlobalAttrib(void)
{
  int size = 0;
  int is_bold = 0,
    is_italic = 0, 
    is_underline = 0,
    is_strikeout = 0;
  char typeface[1024];

  char* font = IupGetGlobal("DEFAULTFONT");

  if (!iupGetFontInfo(font, typeface, &size, &is_bold, &is_italic, &is_underline, &is_strikeout))
    return NULL;

  return iupStrReturnInt(size);
}

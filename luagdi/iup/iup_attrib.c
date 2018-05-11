#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <limits.h>
#include <stdarg.h>
#include <windows.h>

#include <lua.h>
#include <lauxlib.h>

#include "iup_op.h"
#include "iupdraw.h"
#include "iup_drvdraw.h"
#include "iup_assert.h"
#include "iup_attrib.h"
#include "iup_font.h"

static Itable *iglobal_table = NULL;

int iupStrEqual(const char* str1, const char* str2) 
{
#define EXTRAINC(_x) (void)(_x)
#define SF(_x) (_x)
  IUP_STR_EQUAL(str1, str2);
#undef SF
#undef EXTRAINC
  return 0;
}

//windows///////////////////////////////////////////////////////////////////////////////


void iupdrvGetScreenSize(int *width, int *height)
{
  RECT area;
  SystemParametersInfoA(SPI_GETWORKAREA, 0, &area, 0);
  *width = (int)(area.right - area.left);
  *height =  (int)(area.bottom - area.top);
}

void iupdrvAddScreenOffset(int *x, int *y, int add)
{
  RECT area;
  SystemParametersInfoA(SPI_GETWORKAREA, 0, &area, 0);
  if (add==1)
  {
    if (x) *x += area.left;
    if (y) *y += area.top;
  }
  else
  {
    if (x) *x -= area.left;
    if (y) *y -= area.top;
  }
}

int iupdrvGetScreenDepth(void)
{
  int bpp;
  HDC hDCDisplay = GetDC(NULL);
  bpp = GetDeviceCaps(hDCDisplay, BITSPIXEL);
  ReleaseDC(NULL, hDCDisplay);
  return bpp;
}

float iupdrvGetScreenDpi(void)
{
  float dpi;
  HDC hDCDisplay = GetDC(NULL);
  dpi = (float)GetDeviceCaps(hDCDisplay, LOGPIXELSY);
  ReleaseDC(NULL, hDCDisplay);
  return dpi;
}
char* iupdrvLocaleInfo(void)
{
  CPINFOEXA info;
  GetCPInfoExA(CP_ACP, 0, &info);
  return iupStrReturnStr(info.CodePageName);
}

int iupdrvGetScrollbarSize(void)
{
  int xv = GetSystemMetrics(SM_CXVSCROLL);
  int yh = GetSystemMetrics(SM_CYHSCROLL);
  return xv > yh ? xv : yh;
}

char* iupdrvGetGlobal(const char* name)
{
	/*UGLY
  if (iupStrEqual(name, "VIRTUALSCREEN"))
  {
    int x = GetSystemMetrics(SM_XVIRTUALSCREEN); 
    int y = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int w = GetSystemMetrics(SM_CXVIRTUALSCREEN); 
    int h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    return iupStrReturnStrf("%d %d %d %d", x, y, w, h);
  }
  if (iupStrEqual(name, "MONITORSINFO"))
  {
    int i;
    int monitors_count = GetSystemMetrics(SM_CMONITORS);
    RECT* monitors_rect = malloc(monitors_count*sizeof(RECT));
    char* str = iupStrGetMemory(monitors_count*50);
    char* pstr = str;

    win_monitor_index = 0;
    EnumDisplayMonitors(NULL, NULL, winGlobalMonitorInfoEnum, (LPARAM)monitors_rect);

    for (i=0; i < monitors_count; i++)
      pstr += sprintf(pstr, "%d %d %d %d\n", (int)monitors_rect[i].left, (int)monitors_rect[i].top, (int)(monitors_rect[i].right-monitors_rect[i].left), (int)(monitors_rect[i].bottom-monitors_rect[i].top));

    free(monitors_rect);
    return str;
  }
  if (iupStrEqual(name, "MONITORSCOUNT"))
  {
    int monitors_count = GetSystemMetrics(SM_CMONITORS);
    return iupStrReturnInt(monitors_count);
  }
  if (iupStrEqual(name, "TRUECOLORCANVAS"))
  {
    return iupStrReturnBoolean(iupdrvGetScreenDepth() > 8);
  }
  if (iupStrEqual(name, "UTF8MODE"))
  {
    return iupStrReturnBoolean(iupwinStrGetUTF8Mode());
  }
  if (iupStrEqual(name, "UTF8MODE_FILE"))
  {
    return iupStrReturnBoolean(iupwinStrGetUTF8ModeFile());
  }
  if (iupStrEqual(name, "DLL_HINSTANCE"))
  {
    return (char*)iupwin_dll_hinstance;
  }
  if (iupStrEqual(name, "HINSTANCE"))
  {
    return (char*)iupwin_hinstance;
  }
  if (iupStrEqual(name, "COMCTL32VER6"))
  {
    return iupStrReturnBoolean(iupwin_comctl32ver6);
  }
  if (iupStrEqual(name, "SYSTEMCODEPAGE"))
  {
    CPINFOEX info;
    GetCPInfoEx(CP_ACP, 0, &info);
    return iupStrReturnInt(info.CodePage);
  }
  if (iupStrEqual(name, "LASTERROR"))
  {
    DWORD error = GetLastError();
    if (error)
    {
      LPTSTR lpMsgBuf = NULL;
      FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
                    FORMAT_MESSAGE_FROM_SYSTEM|
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, error, 0, 
                    (LPTSTR)&lpMsgBuf,  
                    0, NULL);
      if (lpMsgBuf)
      {
        char* str = iupStrReturnStr(iupwinStrFromSystem(lpMsgBuf));
        LocalFree(lpMsgBuf);
        return str;
      }
      else
        return "Unknown Error";
    }
  }
  if (iupStrEqual(name, "EXEFILENAME"))
  {
    TCHAR filename[10240];
    GetModuleFileName(NULL, filename, 10240);
    return iupStrReturnStr(iupwinStrFromSystemFilename(filename));
  }
  if (iupStrEqual(name, "DWM_COMPOSITION"))
  {
    typedef HRESULT(STDAPICALLTYPE *PtrDwmIsCompositionEnabled)(BOOL*);
    static PtrDwmIsCompositionEnabled dwmIsCompositionEnabled = NULL;
    if (dwmIsCompositionEnabled == NULL) 
    {
      HMODULE dwmLibrary = LoadLibrary(TEXT("dwmapi.dll"));
      if (dwmLibrary)
        dwmIsCompositionEnabled = (PtrDwmIsCompositionEnabled)GetProcAddress(dwmLibrary, "DwmIsCompositionEnabled");
    }
    if (dwmIsCompositionEnabled != NULL) 
    {
     
      BOOL enabled;
      dwmIsCompositionEnabled(&enabled);
      return iupStrReturnBoolean(enabled);
    }
    else
      return NULL;
  }
  */
  return NULL;
}

//windows///////////////////////////////////////////////////////////////////////////////
static char *iStrDupUntilNoCase(char **str, char sep)
{
  char *p_str,*new_str;
  if (!str || str[0]==0)
    return NULL;

  p_str=strchr(*str,sep); /* usually the lower case is enough */
  if (!p_str && (iup_toupper(sep)!=sep)) 
    p_str=strchr(*str, iup_toupper(sep));  /* but check also for upper case */

  /* if both fail, then abort */
  if (!p_str) 
    return NULL;
  else
  {
    int i;
    int sl=(int)(p_str - (*str));

    new_str = (char *) malloc (sl + 1);
    if (!new_str) return NULL;

    for (i = 0; i < sl; ++i)
      new_str[i] = (*str)[i];

    new_str[sl] = 0;

    *str = p_str+1;
    return new_str;
  }
}


int iupStrToInt(const char *str, int *i)
{
  if (!str) return 0;
  if (sscanf(str, "%d", i) != 1) return 0;
  return 1;
}

int iupStrToIntInt(const char *str, int *i1, int *i2, char sep)
{
  if (!str) return 0;
                         
  if (iup_tolower(*str) == sep) /* no first value */
  {
    str++; /* skip separator */
    if (sscanf(str, "%d", i2) != 1) return 0;
    return 1;
  }
  else 
  {
    char* p_str = iStrDupUntilNoCase((char**)&str, sep);
    
    if (!p_str)   /* no separator means no second value */
    {        
      if (sscanf(str, "%d", i1) != 1) return 0;
      return 1;
    }
    else if (*str==0)  /* separator exists, but second value empty, also means no second value */
    {        
      int ret = sscanf(p_str, "%d", i1);
      free(p_str);
      if (ret != 1) return 0;
      return 1;
    }
    else
    {
      int ret = 0;
      if (sscanf(p_str, "%d", i1) == 1) ret++;
      if (sscanf(str, "%d", i2) == 1) ret++;
      free(p_str);
      return ret;
    }
  }
}

static const char* iClassFindId(const char* name)
{
  while(*name)
  {
    if (*name >= '0' && *name <= '9')
      return name;
    if (IUP_CHECKIDSEP(name))
      return name;

    name++;
  }
  return NULL;
}

static const char* iClassCutNameId(const char* name, const char* name_id)
{
  static char str[100];
  int len = (int)(name_id - name);
  if (len == 0)
    return NULL;

  memcpy(str, name, len);
  str[len] = 0;
  return str;
}


void iupdrvGetCursorPos(int *x, int *y)
{
  POINT CursorPoint;
  GetCursorPos(&CursorPoint);
  *x = (int)CursorPoint.x;
  *y = (int)CursorPoint.y;

  iupdrvAddScreenOffset(x, y, -1);
}

void iupdrvGetFullSize(int *width, int *height)
{
  RECT rect;
  GetWindowRect(GetDesktopWindow(), &rect);
  *width = rect.right - rect.left;
  *height = rect.bottom - rect.top;
}
char* IupGetGlobal(const char *name)
{
  char* value;
  
  iupASSERT(name!=NULL);
  if (!name) 
    return NULL;

  if (iupStrEqual(name, "DEFAULTFONTSIZE"))
    return iupGetDefaultFontSizeGlobalAttrib();
  if (iupStrEqual(name, "DEFAULTFONTSTYLE"))
    return iupGetDefaultFontStyleGlobalAttrib();
  if (iupStrEqual(name, "DEFAULTFONTFACE"))
    return iupGetDefaultFontFaceGlobalAttrib();
 
	if (iupStrEqual(name, "CURSORPOS"))
  {
    int x, y;
    iupdrvGetCursorPos(&x, &y);
    return iupStrReturnIntInt(x, y, 'x');
  }
  if (iupStrEqual(name, "SHIFTKEY"))
  {
    char key[5];
    iupdrvGetKeyState(key);
    return iupStrReturnChecked(key[0] == 'S');
  }
 
  if (iupStrEqual(name, "CONTROLKEY"))
  {
    char key[5];
    iupdrvGetKeyState(key);
    return iupStrReturnChecked(key[1] == 'C');
  }
  if (iupStrEqual(name, "MODKEYSTATE"))
  {
    char *str = iupStrGetMemory(5);
    iupdrvGetKeyState(str);
    return str;
  }
  if (iupStrEqual(name, "SCREENSIZE"))
  {
    int w, h;
    iupdrvGetScreenSize(&w, &h);
    return iupStrReturnIntInt(w, h, 'x');
  }
  if (iupStrEqual(name, "FULLSIZE"))
  {
    int w, h;
    iupdrvGetFullSize(&w, &h);
    return iupStrReturnIntInt(w, h, 'x');
  }
  if (iupStrEqual(name, "SCREENDEPTH"))
  {
    int bpp = iupdrvGetScreenDepth();
    return iupStrReturnInt(bpp);
  }
  if (iupStrEqual(name, "SCREENDPI"))
  {
    float dpi = iupdrvGetScreenDpi();
    return iupStrReturnFloat(dpi);
  }
  if (iupStrEqual(name, "SYSTEMLOCALE"))
    return iupdrvLocaleInfo();
  if (iupStrEqual(name, "SCROLLBARSIZE"))
    return iupStrReturnInt(iupdrvGetScrollbarSize());

  value = iupdrvGetGlobal(name);

  if (!value)
    value = (char*)iupTableGet(iglobal_table, name);
/**/
  return value;
}



static unsigned int iTableGetEntryIndex(Itable *it, const char *key, unsigned long *keyIndex)
{
  if (it->indexType == IUPTABLE_STRINGINDEXED)
  {
    register unsigned int checksum = 0;

/*     Orignal version
    unsigned int i;
    for (i = 0; key[i]; i++)
      checksum = checksum*31 + key[i];  
*/

    while (*key)
    {
      checksum *= 31;
      checksum += *key;
      key++;
    }

    *keyIndex = checksum;            /* this could NOT be dependent from table size */
  }
  else
  {
    /* Pointer indexed */
    *keyIndex = (unsigned long)key;   /* this could NOT be dependent from table size */
  }

  return (unsigned int)((*keyIndex) % it->entriesSize);
}


static unsigned int iTableFindItem(Itable *it, const char *key, ItableEntry **entry, 
                                                          unsigned int *itemIndex,
                                                          unsigned long *keyIndex)
{
  unsigned int entryIndex,
               itemFound,
               i;
  ItableItem  *item;

  entryIndex = iTableGetEntryIndex(it, key, keyIndex);

  *entry = &(it->entries[entryIndex]);

  item = &((*entry)->items[0]);
  for (i = 0; i < (*entry)->nextItemIndex; i++, item++)
  {
    if (it->indexType == IUPTABLE_STRINGINDEXED)
      itemFound = item->key.keyIndex == *keyIndex; 
/*    itemFound = iupStrEqual(item->key.keyStr, key);  This is the original safe version */
    else
      itemFound = item->key.keyStr == key;

    if (itemFound)
    {
      *itemIndex = i;
      return 1;
    }
  }

  /* if not found "entry", "itemIndex" and "keyIndex" will have the new insert position. */

  *itemIndex = i;
  return 0;
}


void *iupTableGet(Itable *it, const char *key)
{
  unsigned int  itemFound,
                itemIndex;
  unsigned long keyIndex;
  ItableEntry  *entry;
  void         *value = 0;

  iupASSERT(it!=NULL);
  iupASSERT(key!=NULL);
  if (!it || !key)
    return 0;

  itemFound = iTableFindItem(it, key, &entry, &itemIndex, &keyIndex);
  if (itemFound)
    value = entry->items[itemIndex].value;

  return value;
}

char* iupAttribGet(Ihandle* ih, const char* name)
{
  if (!ih || !name)
    return NULL;
  return iupTableGet(ih->attrib, name);
}

static char* iClassGetDefaultValue(IattribFunc* afunc)
{
  if (afunc->call_global_default)
    return IupGetGlobal(afunc->default_value);
  else
    return (char*)afunc->default_value;
}

char* iupClassObjectGetAttribute(Ihandle* ih, const char* name, char* *def_value, int *inherit)
{
  IattribFunc* afunc;

  if (ih->iclass->has_attrib_id!=0)
  {
    const char* name_id = iClassFindId(name);
    if (name_id)
    {
      const char* partial_name = iClassCutNameId(name, name_id);
      if (!partial_name)
        partial_name = "IDVALUE";  
      afunc = (IattribFunc*)iupTableGet(ih->iclass->attrib_func, partial_name);
      if (afunc && afunc->flags & IUPAF_HAS_ID)
      {
        *def_value = NULL;  
        *inherit = 0;      

        if (afunc->flags & IUPAF_WRITEONLY)
          return NULL;

        if (afunc->get && (ih->handle || afunc->flags & IUPAF_NOT_MAPPED))
        {
          if (afunc->flags & IUPAF_HAS_ID2)
          {
            IattribGetId2Func id2_get = (IattribGetId2Func)afunc->get;
            int id1=IUP_INVALID_ID, id2=IUP_INVALID_ID;
            iupStrToIntInt(name_id, &id1, &id2, ':');
            return id2_get(ih, id1, id2);
          }
          else
          {
            IattribGetIdFunc id_get = (IattribGetIdFunc)afunc->get;
            int id=IUP_INVALID_ID;
            if (iupStrToInt(name_id, &id))
              return id_get(ih, id);
          }
        }
        else
          return NULL;     
      }
    }
  }

 

  afunc = (IattribFunc*)iupTableGet(ih->iclass->attrib_func, name);
  *def_value = NULL;
  *inherit = 1; 
  if (afunc)
  {
    *def_value = iClassGetDefaultValue(afunc);
    *inherit = !(afunc->flags & IUPAF_NO_INHERIT) &&   
               !(afunc->flags & IUPAF_NO_STRING);     

    if (afunc->flags & IUPAF_WRITEONLY)
      return NULL;

    if (afunc->get && (ih->handle || afunc->flags & IUPAF_NOT_MAPPED))
    {
      if (afunc->flags & IUPAF_HAS_ID2)
      {
        IattribGetId2Func id2_get = (IattribGetId2Func)afunc->get;
        return id2_get(ih, IUP_INVALID_ID, IUP_INVALID_ID); 
      }
      else if (afunc->flags & IUPAF_HAS_ID)
      {
        IattribGetIdFunc id_get = (IattribGetIdFunc)afunc->get;
        return id_get(ih, IUP_INVALID_ID); 
      }
      else
        return afunc->get(ih);
    }
  }
  
  
  return NULL;
}

char* IupGetAttribute(Ihandle *ih, const char* name)
{
  iupASSERT(name!=NULL);
  if (!name)
    return NULL;

  if (!ih)
    return IupGetGlobal(name);

  iupASSERT(iupObjectCheck(ih));
  if (!iupObjectCheck(ih))
    return NULL;

  if (iupATTRIB_ISINTERNAL(name))
    return iupAttribGet(ih, name);
  else
  {
    int inherit;
    char *value, *def_value;

    value = iupClassObjectGetAttribute(ih, name, &def_value, &inherit);

    if (!value)
      value = iupAttribGet(ih, name);

    if (!value && inherit)
    {
      while (!value)
      {
        ih = ih->parent;
        if (!ih)
          break;

        value = iupAttribGet(ih, name);
      }
    }

    if (!value)
      value = def_value;

    return value;
  }
}


int iupStrToRGB(const char *str, unsigned char *r, unsigned char *g, unsigned char *b)
{
  unsigned int ri = 0, gi = 0, bi = 0;
  if (!str) return 0;
  if (str[0]=='#')
  {
    str++;
    if (sscanf(str, "%2X%2X%2X", &ri, &gi, &bi) != 3) return 0;
  }
  else
  {
    if (sscanf(str, "%u %u %u", &ri, &gi, &bi) != 3) return 0;
  }
  if (ri > 255 || gi > 255 || bi > 255) return 0;
  *r = (unsigned char)ri;
  *g = (unsigned char)gi;
  *b = (unsigned char)bi;
  return 1;
}

void IupGetRGB(Ihandle *ih, const char* name, unsigned char *r, unsigned char *g, unsigned char *b)
{
  iupStrToRGB(IupGetAttribute(ih, name), r, g, b);
}

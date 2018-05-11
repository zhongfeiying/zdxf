
#ifndef __IUP_ATTRIB_H 
#define __IUP_ATTRIB_H



#include "iup_object.h"

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////

#define IUP_CHECKIDSEP(_str) (*(_str) == '*' || *(_str) == ':' || *(_str) == '-')
#define iupATTRIB_ISINTERNAL(_name) ((_name[0] == '_' && _name[1] == 'I' && _name[2] == 'U' && _name[3] == 'P')? 1: 0)
#define iup_toupper(_c)  ((_c >= 'a' && _c <= 'z')? (_c - 'a') + 'A': _c)
#define iup_tolower(_c)  ((_c >= 'A' && _c <= 'Z')? (_c - 'A') + 'a': _c)
/////////////////////////////////


#define IUP_STR_EQUAL(str1, str2)      \
{                                      \
  if (str1 == str2)                    \
    return 1;                          \
                                       \
  if (!str1 || !str2)                  \
    return 0;                          \
                                       \
  while(*str1 && *str2 &&              \
        SF(*str1) == SF(*str2))        \
  {                                    \
    EXTRAINC(str1);                    \
    EXTRAINC(str2);                    \
    str1++;                            \
    str2++;                            \
  }                                    \
                                       \
  /* check also for terminator */      \
  if (*str1 == *str2) return 1;        \
}


typedef char* (*IattribGetId2Func)(Ihandle* ih, int id1, int id2);
typedef char* (*IattribGetIdFunc)(Ihandle* ih, int id);

/** Attribute flags.
 * Used by \ref iupClassRegisterAttribute.
 * \ingroup iclass */
typedef enum _IattribFlags{
  IUPAF_DEFAULT=0,     /**< inheritable, can has a default value, is a string, can call the set/get functions only if mapped, no ID */
  IUPAF_NO_INHERIT=1,  /**< is not inheritable */
  IUPAF_NO_DEFAULTVALUE=2,  /**< can not has a default value */
  IUPAF_NO_STRING=4,   /**< is not a string */
  IUPAF_NOT_MAPPED=8,  /**< will call the set/get functions also when not mapped */
  IUPAF_HAS_ID=16,     /**< can has an ID at the end of the name, automatically set by \ref iupClassRegisterAttributeId */
  IUPAF_READONLY=32,   /**< is read-only, can not be changed */
  IUPAF_WRITEONLY=64,  /**< is write-only, usually an action */
  IUPAF_HAS_ID2=128,   /**< can has two IDs at the end of the name, automatically set by \ref iupClassRegisterAttributeId2 */
  IUPAF_CALLBACK=256,  /**< is a callback, not an attribute */
  IUPAF_NO_SAVE=512,   /**< can NOT be directly saved, should have at least manual processing */
  IUPAF_NOT_SUPPORTED=1024,  /**< not supported in that driver */
  IUPAF_IHANDLENAME=2048,    /**< is an Ihandle* name, associated with IupSetHandle */
  IUPAF_IHANDLE=4096         /**< is an Ihandle* */
} IattribFlags;

//////////////////////////////////
typedef int (*IattribSetFunc)(Ihandle* ih, const char* value);
typedef char* (*IattribGetFunc)(Ihandle* ih);
typedef struct _IattribFunc
{
  IattribGetFunc get;
  IattribSetFunc set;
  const char* default_value;
  const char* system_default;
  int call_global_default;
  int flags;
} IattribFunc;
//windows///////////////////////////////
void iupdrvAddScreenOffset(int *x, int *y, int add);
void iupdrvGetCursorPos(int *x, int *y);
void iupdrvGetScreenSize(int *width, int *height);
int iupdrvGetScreenDepth(void);
float iupdrvGetScreenDpi(void);
char* iupdrvLocaleInfo(void);
int iupdrvGetScrollbarSize(void);
char* iupdrvGetGlobal(const char* name);
void iupdrvGetFullSize(int *width, int *height);

/////////////////////////////////
int iupStrEqual(const char* str1, const char* str2) ;

/////////////////////////////////
int iupStrToInt(const char *str, int *i);
int iupStrToIntInt(const char *str, int *i1, int *i2, char sep);

char* iupClassObjectGetAttribute(Ihandle* ih, const char* name, char* *def_value, int *inherit);
char* iupAttribGet(Ihandle* ih, const char* name);
int iupStrToRGB(const char *str, unsigned char *r, unsigned char *g, unsigned char *b);
void *iupTableGet(Itable *it, const char *key);

/////////////////////////////////
char* IupGetGlobal(const char *name);
char* IupGetAttribute(Ihandle *ih, const char* name);
void IupGetRGB(Ihandle *ih, const char* name, unsigned char *r, unsigned char *g, unsigned char *b);


#ifdef __cplusplus
}
#endif


#endif
#ifndef __IUP_OBJECT_H 
#define __IUP_OBJECT_H


#include <stdarg.h>
#include "iup_class.h"

/** A simple definition that do not depends on the native system, 
   but helps a lot when writing native code. See \ref iup_object.h for definitions.
 * \ingroup object */
#if defined(GTK_MAJOR_VERSION)
typedef struct _GtkWidget InativeHandle;
#elif defined(XmVERSION)
typedef struct _WidgetRec InativeHandle;
#elif defined(WINVER)
typedef struct HWND__ InativeHandle;
#else
typedef struct _InativeHandle InativeHandle;
#endif


typedef struct Ihandle_ Ihandle;

/** Structure used by all the elements.
 * \ingroup object */
struct Ihandle_
{
  char sig[4];           /**< IUP Signature, initialized with "IUP", cleared on destroy */
  Iclass* iclass;        /**< Ihandle Class */
  Itable* attrib;        /**< attributes table */
  int serial;            /**< serial number used for controls that need a numeric id, initialized with -1 */
  InativeHandle* handle; /**< native handle. initialized when mapped. InativeHandle definition is system dependent. */
  int expand;            /**< expand configuration, a combination of \ref Iexpand, for containers is a combination of the children expand's */
  int flags;             /**< flags configuration, a combination of \ref Iflags */
  int x, y;              /**< upper-left corner relative to the native parent. always 0 for the dialog. */
  int    userwidth,    userheight; /**< user defined size for the control using SIZE or RASTERSIZE */
  int naturalwidth, naturalheight; /**< the calculated size based in the control contents and the user size */
  int currentwidth, currentheight; /**< actual size of the control in pixels (window size, including decorations and margins). */
  Ihandle* parent;       /**< previous control in the hierarchy tree */
  Ihandle* firstchild;   /**< first child control in the hierarchy tree */
  Ihandle* brother;      /**< next control inside parent */
//  IcontrolData* data;    /**< private control data. automatically freed if not NULL in destroy */
};





/** Checks if the handle is still valid based on the signature.
 * But if the handle was destroyed still can access invalid memory.
 * \ingroup object */
int iupObjectCheck(Ihandle* ih);


#endif
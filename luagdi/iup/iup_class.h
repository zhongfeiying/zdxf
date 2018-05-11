#ifndef __IUP_CLASS_H 
#define __IUP_CLASS_H


#include "iup_table.h"

typedef struct Iclass_ Iclass;

struct Iclass_
{
  /* Class configuration parameters. */
  const char* name;     /**< class name. No default, must be initialized. */
  const char* format;   /**< Creation parameters format of the class. \n
                   * Used only for LED parsing. \n
                   * It can have none (NULL), one or more of the following.
                   * - "b" = (unsigned char) - byte
                   * - "c" = (unsigned char*) - array of byte
                   * - "i" = (int) - integer
                   * - "j" = (int*) - array of integer
                   * - "f" = (float) - real
                   * - "s" = (char*) - string 
                   * - "a" = (char*) - name of the ACTION callback
                   * - "h" = (Ihandle*) - element handle
                   * - "g" = (Ihandle**) - array of element handle */
  int childtype;   /**< children count enum: none, many, or n, as described in \ref IchildType. Default is IUP_CHILDNONE. \n
                    * This identifies a container that can be manipulated with IupReparent, IupAppend and IupInsert. \n
                    * Used to control the allowed number of children and define its behavior in the layout processing. \n
                    * The element can still have hidden children even if this is none. */
  int is_interactive; /**< keyboard interactive boolean, 
                       * true if the class can have the keyboard input focus. Default is false. */
  int has_attrib_id;  /**< indicate if any attribute is numbered. Default is not. Can be 1 or 2. */

  Iclass* parent; /**< class parent to implement inheritance.
                   * Class name must be different. \n
                   * Creation parameters should be the same or replace the parents creation function. \n
                   * Native type should be the same.  \n
                   * Child type should be a more restrictive or equal type (many->one->none). \n
                   * Attribute functions will have only one common table. \n
                   * All methods can be changed, set to NULL, switched, etc. */

  Itable* attrib_func; /**< table of functions to handle attributes, only one per class tree */

};




#endif
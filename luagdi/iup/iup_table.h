#ifndef __IUP_TABLE_H 
#define __IUP_TABLE_H


#include <stdarg.h>



/** How the table key is interpreted.
 * \ingroup table */
typedef enum _Itable_IndexTypes
{
  IUPTABLE_POINTERINDEXED = 10, /**< a pointer address is used as key. */
  IUPTABLE_STRINGINDEXED        /**< a string as key */
} Itable_IndexTypes;
/** How the value is interpreted.
 * \ingroup table */
typedef enum _Itable_Types
{
  IUPTABLE_POINTER,     /**< regular pointer for strings and other pointers */
  IUPTABLE_STRING,      /**< string duplicated internally */
  IUPTABLE_FUNCPOINTER  /**< function pointer */
} Itable_Types;

/* Iteration context.
 */
typedef struct _ItableContext
{
  unsigned int entryIndex;  /* index at the Itable::entries array */
  unsigned int itemIndex;   /* index at the ItableEntry::items array */
} ItableContext;

/* A key of an item.
 * To avoid lots of string comparisions we store
 * a keyindex as an integer.
 * To find a key in an item list we only have to
 * do integer comparisions.
 * Additionally the key itself is stored in
 * keyStr. In a string indexed hashtable this is
 * a duplicated string, in a pointer indexed hash table
 * this is simply the pointer (in this case keyIndex
 * and keyStr are equal).
*/
typedef struct _ItableKey
{
  unsigned long keyIndex;  /* the secondary hash number */
  const char   *keyStr;
}
ItableKey;

/* An item in the hash table.
 * Such an item is stored in the item list of
 * an entry.
 */
typedef struct _ItableItem
{
  Itable_Types  itemType;
  ItableKey     key;
  void*         value;
}
ItableItem;

/* An entry in the hash table.
 * An entry is chosen by an index in the hash table
 * and contains a list of items.
 * The number of items in this list is stored
 * in nextItemIndex.
 * size is the current size of the items array.
 */
typedef struct _ItableEntry
{
  unsigned int  nextItemIndex;
  unsigned int  itemsSize;
  ItableItem*   items;
}
ItableEntry;


/* A hash table.
 * entries is an array of entries. Select an
 * entry by its index.
 * size is the number of entries in the hash table...
 */
struct _Itable
{
  unsigned int         entriesSize;
  unsigned int         numberOfEntries;
  unsigned int         tableSizeIndex;  /* index into itable_hashTableSize array */
  Itable_IndexTypes    indexType;  /* type of the index: string or pointer. */
  ItableEntry          *entries;
  ItableContext        context;
};


typedef struct _Itable Itable;
#endif
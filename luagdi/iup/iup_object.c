#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iupdraw.h"
#include "iup_drvdraw.h"
#include "iup_assert.h"


int iupObjectCheck(Ihandle* ih)
{
  char* sig = (char*)ih;

  if (!ih) return 0;  

  if (sig[0] != 'I' ||
      sig[1] != 'U' ||
      sig[2] != 'P' ||
      sig[3] != 0)
    return 0;

  return 1;
}

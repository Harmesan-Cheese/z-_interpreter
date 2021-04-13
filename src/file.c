#include "file.h"
#include <stdlib.h>

SOURCE_T *initsource(char *src)
{
   SOURCE_T *source;
   source = calloc(4, sizeof(SOURCE_T));

   source->src = src;
   source->charat = 0;
   source->line = 1;
   source->c = (char)source->src[source->charat];

   return source;
}

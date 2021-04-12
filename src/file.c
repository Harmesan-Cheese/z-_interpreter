#include "file.h"
#include <stdlib.h>

SOURCE *initsource(char *src)
{
   SOURCE *source;
   source = calloc(3, sizeof(SOURCE));

   source->src = src;
   source->charat = 0;
   source->line = 1;

   return source;
}

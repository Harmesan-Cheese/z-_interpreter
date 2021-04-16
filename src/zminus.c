#include "zminus.h"
#include <stdio.h>

void zminusinterpret(char *src)
{
   SOURCE_T *source = initsource(src);
   PARSER_T *parser = initparser(source);
   AST_T *root = parse(parser);
}

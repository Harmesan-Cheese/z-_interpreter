#include "zminus.h"
#include <stdio.h>

void zminusinterpret(char *src)
{
   SOURCE_T *source = initsource(src);
   TOKEN_T *token;
   AST_T *ast;
   

   while(1)
   {
      ast = parseprg(source);
      printf("TYPE: %d, VALUE: %d\n", ast->type, ast->value);
   }
}

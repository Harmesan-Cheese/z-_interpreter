#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

AST_T *initast(int type)
{
   AST_T *ast = calloc(1, sizeof(struct AST));
   ast->type = type;

   if (type == COMPOUND)
   {
      ast->children = initlist(sizeof(struct AST*));
   }
   return ast;
}

int strtoint(char *str)
{
   int val = 0;
   int i;

   for (i = 0; str[i] != '\0'; i++)
   {
      val += str[i];
   }
   
   return val;
}

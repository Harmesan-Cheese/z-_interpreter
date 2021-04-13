#include "zminus.h"
#include <stdio.h>

void zminusinterpret(char *src)
{
   SOURCE_T *source = initsource(src);
   TOKEN_T *token;
   
   while (token->tokentype != END)
   {
      token = parsetoken(source);
      printf("TOKEN: ( %s ), TYPE: %d\n", token->value, token->tokentype);
   }
}

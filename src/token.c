#include "token.h"
#include <stdlib.h>

TOKEN *inittoken(int tokentype, char *value)
{
   TOKEN *token;
   token = calloc(2, sizeof(TOKEN));

   token->tokentype = tokentype;
   token->value = value;

   return token;
}

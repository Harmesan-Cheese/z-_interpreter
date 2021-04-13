#include "token.h"
#include "file.h"
#include <stdlib.h>
#include <string.h>

int isletter(char c)
{
   return 0;
}

int isnum(char c)
{
   return 0;
}

TOKEN_T *inittoken(int tokentype, char *value)
{
   TOKEN_T *token;
   token = calloc(2, sizeof(TOKEN_T));

   token->tokentype = tokentype;
   token->value = value;

   return token;
}

TOKEN_T *parseidtoken(SOURCE_T *source)
{
   char *value = malloc(sizeof(char));

   while(isletter(source->c))
   {
      value = realloc(value, (strlen(value) + 2) * sizeof(char));
      strcat(value, &source->c);
      source->charat++;
      source->c = source->src[source->charat];
   }

   source->charat--;
   source->c = source->src[source->charat];

   return inittoken(ID, value);
}

TOKEN_T *parsenumbertoken(SOURCE_T *source)
{
   char *value = malloc(sizeof(char));

   while(isnum(source->c))
   {
      value = realloc(value, (strlen(value) + 2) * sizeof(char));
      strcat(value, &source->c);
      source->charat++;
      source->c = source->src[source->charat];
   }

   source->charat--;
   source->c = source->src[source->charat];

   return inittoken(NUMBER, value);
}

TOKEN_T *parsetoken(SOURCE_T *source)
{
   int returned = 0;

   switch(source->c)
   {
      case 'a':
         return parseidtoken(source);
         returned = 1;
         break;
      case '(':
         return inittoken(LEFT_PAREN, "(");
         returned = 1;
         break;
      case ')':
         return inittoken(RIGHT_PAREN, ")");
         returned = 1;
         break;
      case '{':
         return inittoken(LEFT_BRACE, "{");
         returned = 1;
         break;
      case '}':
         return inittoken(RIGHT_BRACE, "}");
         returned = 1;
         break;
      case '=':
         return ((source->src[source->charat + 1]) == '=') ? inittoken(EQUAL_EQUAL, "==") : inittoken(EQUAL, "=");
         returned = 1;
         break;
      case 'v':
         if (source->src[source->charat + 1] == 'a' && source->src[source->charat + 2] == 'r' && source->src[source->charat + 3] == ' ')
            return inittoken(VAR, "var");
         returned = 1;
         break;
      case '0':
         return parsenumbertoken(source);
         returned = 1;
         break;
      case '\n':
         return inittoken(NEWLINE, "\n");
         source->line++;
         returned = 1;
         break;
      case '\0':
         return inittoken(END, "");
         source->charat--;
         source->c = source->src[source->charat];
         returned = 1;
         break;
   }
   source->charat++;
   source->c = source->src[source->charat];
   
   if (returned == 0)
      return inittoken(NOTHING, "");
}

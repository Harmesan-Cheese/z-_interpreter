#include "token.h"
#include "file.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void advance(SOURCE_T *source)
{
   if (source->c != '\0')
   {
      source->charat++;
      source->c = source->src[source->charat];
   }
}

char peek(SOURCE_T *source, int offset)
{
   return source->src[source->charat + offset];
}

void skipwhitespace(SOURCE_T *source)
{
   while(source->c == ' ' || source->c == '\t')
      advance(source);
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

   while(isalpha(source->c))
   {
      value = realloc(value, (strlen(value) + 2) * sizeof(char));
      strcat(value, &source->c);
      advance(source);
   }

   return inittoken(ID, value);
}

TOKEN_T *parsenumbertoken(SOURCE_T *source)
{
   char *value = malloc(sizeof(char));

   while(isdigit(source->c))
   {
      value = realloc(value, (strlen(value) + 2) * sizeof(char));
      strcat(value, (char[]){source->c, 0});
      advance(source);
   }

   return inittoken(NUMBER, value);
}

TOKEN_T *consumecurrent(SOURCE_T *source, int tokentype)
{
   char *value = calloc(2, sizeof(char));
   value[0] = source->c;
   value[1] = '\0';

   TOKEN_T *token = inittoken(tokentype, value);
   advance(source);

   return token;
}

TOKEN_T *consume(SOURCE_T *source, TOKEN_T *token)
{
   advance(source);
   return token;
}

TOKEN_T *parsetoken(SOURCE_T *source)
{
   while (source->c != '\0')
   {
      skipwhitespace(source);

      if (isalpha(source->c))
      {
         if (source->c == 'v' && peek(source, 1) == 'a' && peek(source, 2) == 'r' && peek(source, 3 ) == ' ') {
            advance(source);
            advance(source);
            return consume(source, inittoken(VAR, "var"));
            break;
         }
         else if (source->c == 'i' && peek(source, 1) == 'f' && (peek(source, 2) == ' ' || peek(source, 2) == '('))
         {
            advance(source);
            return consume(source, inittoken(IF, "if"));
         }
         else if (source->c == 'p' && peek(source, 1) == 'r' && peek(source, 2) == 'i' && peek(source, 3) == 'n' && peek(source, 4) == 't' && (peek(source, 5) == ' ' || peek(source, 5) == '('))
         {
            advance(source);
            advance(source);
            advance(source);
            advance(source);
            return consume(source, inittoken(PRINT, "print"));
         }
         return parseidtoken(source);
      }
      else if (isdigit(source->c))
      {
         return parsenumbertoken(source);
      }
      switch(source->c)
      {
      case '=': 
         if (peek(source, 1) == '=')
            return consume(source, inittoken(EQUAL_EQUAL, "==")); 
         return consume(source, inittoken(EQUAL, "=")); 
         break;
      case '!':
         if (peek(source, 1) == '=')
            return consume(source, inittoken(NOT_EQUAL, "!="));
         return consumecurrent(source, NOT);
      case '(': return consumecurrent(source, LEFT_PAREN);
      case ')': return consumecurrent(source, RIGHT_PAREN);
      case '{': return consumecurrent(source, LEFT_BRACE);
      case '}': return consumecurrent(source, RIGHT_BRACE);
      case '+': return consumecurrent(source, ADD);
      case '-': return consumecurrent(source, SUB);
      case '*': return consumecurrent(source, MULTIPLE);
      case '/': return consumecurrent(source, DIVIDE);
      case '>': return consumecurrent(source, GREAT_THAN);
      case '<': return consumecurrent(source, LESS_THAN);
      case '\n': source->line++; return consume(source, inittoken(NEWLINE, "n")); source->line++; break;
      default:
         printf("Didn't recognize character: %c", source->c);
      }
   }
   return inittoken(END, 0);
}

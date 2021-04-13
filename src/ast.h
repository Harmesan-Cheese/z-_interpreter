#ifndef AST_H
#define AST_H
#include "list.h"
#include "token.h"

typedef struct AST
{
   enum
   {
      EXPRESSION,
      EQUALITY,
      COMPARISON,
      TERM,
      FACTOR,
      UNARY,
      PRIMARY,
      VARDECL,
      PRINTSTMT,
      BLOCK,
      ERROR
   } type;

   LIST_T *children;
   int value;
   char *name;
} AST_T;

AST_T *initast(int type);
AST_T *parseprg(SOURCE_T *source);
AST_T *parsedecl(TOKEN_T *token, SOURCE_T *source);
AST_T *parsevardecl(TOKEN_T *token, SOURCE_T *source);
AST_T *parsestmt(TOKEN_T *token, SOURCE_T *source);

#endif

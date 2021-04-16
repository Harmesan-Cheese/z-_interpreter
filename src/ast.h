#ifndef AST_H
#define AST_H
#include "list.h"
#include "token.h"
#include "hash.h"

typedef struct AST
{
   enum
   {
      ASSIGNMENT,
      COMPOUND,
      FUNC_DEF,
      DEF_TYPE,
      VARIABLE,
      STMT,
      PRINT,
      NOOP
   } type;

   LIST_T *children;
   char *name;
   struct AST *value;
   struct DATAITEM *var;
} AST_T;

AST_T *initast(int type);
int strtoint(char *str);

#endif

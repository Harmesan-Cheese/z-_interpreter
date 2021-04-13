#include "ast.h"
#include "token.h"
#include "file.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int isliteral(TOKEN_T *token)
{
   switch (token->tokentype)
   {
      case NUMBER:
      case ID:
      case LEFT_PAREN:
         return 0;
      default:
         return 1;
   }
}

AST_T *initast(int type)
{
   AST_T *ast = calloc(1, sizeof(struct AST));
   ast->type = type;

   return ast;
}

AST_T *parseprg(SOURCE_T *source)
{
   TOKEN_T *token;
   AST_T *ast;

  if ((token = parsetoken(source))->tokentype != END)
  {
     return ast = parsedecl(token, source);
  }
  
  ast = initast(ERROR);
  ast->value = -1;
  return ast;
}

AST_T *parsedecl(TOKEN_T *token, SOURCE_T *source)
{
   if (token->tokentype == VAR)
      return parsevardecl(token, source);
   return parsestmt(token, source);
}

AST_T *parsevardecl(TOKEN_T *token, SOURCE_T *source)
{
   char *name;
   AST_T *ast;
   token = parsetoken(source);

   if (token->tokentype == ID)
   {
      name = token->value;
      token = parsetoken(source);
      if (token->tokentype == EQUAL)
      {
         token = parsetoken(source);
         if (isliteral(token))
         {
            ast = initast(VARDECL);
            ast->name = name;
            return ast;
            /* TODO */
         }
         else
         {
            ast = initast(ERROR);
            ast->value = -1;
            return ast;
         }
      }
      ast = initast(VARDECL);
      ast->name = name;
      return ast;

   }
   ast = initast(ERROR);
   ast->value = -1;
   return ast;
}

AST_T *parsestmt(TOKEN_T *token, SOURCE_T *source)
{
   token = parsetoken(source);

   if (token->tokentype == PRINT)
      return initast(PRINTSTMT);
   else if (token->tokentype == LEFT_BRACE)
      return initast(BLOCK); /* TODO add so it runs parsedecl */
   else if (isliteral(token))
      return initast(EXPRESSION);
   AST_T *ast;
   ast = initast(ERROR);
   ast->value = -1;
   return ast;
}

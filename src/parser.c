#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PARSER_T *initparser(SOURCE_T *source)
{
   PARSER_T *parser = calloc(1, sizeof(struct PARSER));
   parser->source = source;
   parser->token = parsetoken(source);

   return parser;
}

TOKEN_T *parsereat(PARSER_T *parser, int type)
{
   if (parser->token->tokentype != type)
   {
      printf("[Parser]: Unexpected token: `%s`, was expecting: `%s`\n", toktostr(parser->token), toktypetostr(type));
      exit(1);
   }

   parser->token = parsetoken(parser->source);
   return parser->token;
}

AST_T* parse(PARSER_T *parser)
{
   return parsecompound(parser);
}

AST_T *parserid(PARSER_T *parser)
{
   char *value = calloc(strlen(parser->token->value) + 1, sizeof(char));
   strcpy(value, parser->token->value);
   parsereat(parser, ID);

   if (parser->token->tokentype == EQUAL)
   {
      parsereat(parser, EQUAL);
      AST_T *ast = initast(ASSIGNMENT);
      ast->var = inithash(ast->var);
      ast->var->key = strtoint(value);
      ast->var->data = evaluate(parser);
      insert(ast->var->key, ast->var->data, ast->var);
      return ast;
   }

   AST_T *ast = initast(VARIABLE);
   ast->name = value;
   return ast;
}

AST_T *parselist(PARSER_T *parser)
{
   parsereat(parser, LEFT_PAREN);
   AST_T *compound = initast(COMPOUND);
   listpush(compound->children, parseexpr(parser));

   while (parser->token->tokentype == COMMA)
   {
      parsereat(parser, COMMA);
      listpush(compound->children, parseexpr(parser));
   }

   parsereat(parser, RIGHT_PAREN);

   return compound;
}

AST_T *parseexpr(PARSER_T *parser)
{
   switch (parser->token->tokentype)
   {
      case VAR:
         parsereat(parser, VAR);
         return parserid(parser);
      case ID: return parserid(parser);
      case LEFT_PAREN: return parselist(parser);
      case PRINT: return parseprint(parser);
      default: printf("[Parser]: Unexpected token `%s`\n", toktostr(parser->token)); exit(1);
   }
}

AST_T *parsecompound(PARSER_T *parser)
{
   AST_T *compound = initast(COMPOUND);

   while (parser->token->tokentype != END)
   {
      listpush(compound->children, parseexpr(parser));
   }

   return compound;
}

AST_T *parseprint(PARSER_T *parser)
{
   parsereat(parser, PRINT);
   AST_T *print = initast(PRINT);
   printf("%d\n", evaluate(parser));
   return print;
}

int evaluate(PARSER_T *parser)
{
   if(parser->token->tokentype == NUMBER)
   {
      int num = atoi(parser->token->value);
      parsereat(parser, NUMBER);

      if (parser->token->tokentype == NEWLINE)
      {
         parsereat(parser, NEWLINE);
         return num;
      }
      else if (parser->token->tokentype == END)
      {
         return num;
      }
   }
   else if(parser->token->tokentype == ID)
   {
      int key = strtoint(parser->token->value);
      parsereat(parser, ID);
      int varnum = search(key)->data;
      if (parser->token->tokentype == NEWLINE)
      {
         parsereat(parser, NEWLINE);
         return varnum;
      }
      else if (parser->token->tokentype == ADD)
      {
         parsereat(parser, ADD);
         if (parser->token->tokentype == ID)
         {
            key = strtoint(parser->token->value);
            parsereat(parser, ID);
            int varnum2 = search(key)->data;
            if (parser->token->tokentype == NEWLINE)
            {
               parsereat(parser, NEWLINE);  
               return varnum + varnum2;
            }
         }
      }
   }
}

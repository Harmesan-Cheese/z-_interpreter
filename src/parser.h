#ifndef PARSER_H
#define PARSER_H

#include "file.h"
#include "token.h"
#include "ast.h"

typedef struct PARSER
{
   SOURCE_T *source;
   TOKEN_T *token;
} PARSER_T;

PARSER_T *initparser(SOURCE_T *source);
TOKEN_T *parsereat(PARSER_T *parser, int type);
AST_T *parse(PARSER_T *parser);
AST_T *parsecompound(PARSER_T *parser);
AST_T *parseexpr(PARSER_T *parser);
int evaluate(PARSER_T *parser);
AST_T *parseprint(PARSER_T *parser);

#endif

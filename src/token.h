#ifndef TOKEN
#define TOKEN

#include "file.h"

typedef struct TOKEN
{
	enum {
      END,
	   ID,
      NUMBER,
      LEFT_PAREN,
		RIGHT_PAREN,
		LEFT_BRACE,
		RIGHT_BRACE,
		EQUAL,
		EQUAL_EQUAL,
		NOT,
		NOT_EQUAL,
		GREAT_THAN,
		LESS_THAN,
		GREAT_THAN_EQUAL,
		LESS_THAN_EQUAL,
		ADD,
		SUB,
		MULTIPLE,
		DIVIDE,
		VAR,
		NEWLINE,
		IF,
		ELSE,
		PRINT,
	   NOTHING
   } tokentype;
   char *value;
} TOKEN_T;

TOKEN_T *inittoken(int tokentype, char *value);
TOKEN_T *parsetoken(SOURCE_T *source);
TOKEN_T *parseidtoken(SOURCE_T *source);
TOKEN_T *parsenumbertoken(SOURCE_T *source);
void skipwhitespace(SOURCE_T *source);
void advance(SOURCE_T *source);
char peek(SOURCE_T *source, int offset);

#endif

typedef struct TOKEN
{
	enum {
	   ID,
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
		PRINT		
	} tokentype;
   char *value;
} TOKEN;

TOKEN *inittoken(int tokentype, char *value);

#ifndef SOURCE
#define SOURCE

typedef struct SOURCE
{
   char *src;
   int charat;
   int line;
   char c;
} SOURCE_T;

SOURCE_T *initsource(char *src);

#endif

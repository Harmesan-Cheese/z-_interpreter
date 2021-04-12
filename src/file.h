typedef struct SOURCE
{
   char *src;
   int charat;
   int line;
} SOURCE;

SOURCE *initsource(char *src);

#include "zminus.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   if (argc < 2)
   {
      printf("Usage: ./zmi <inputfile>\n");
      return 1;
   }

   
   char *src;
   src = readfile(argv[1]);
   zminusinterpret(src);
   free(src);

   return 0;
}

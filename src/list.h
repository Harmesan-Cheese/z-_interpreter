#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct LIST
{
   void **items;
   size_t size;
   size_t itemsize;
} LIST_T;

LIST_T *initlist(size_t itemsize);
void listpush(LIST_T *list, void *item);

#endif

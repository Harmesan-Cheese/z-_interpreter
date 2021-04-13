#include "list.h"

LIST_T *initlist(size_t itemsize)
{
   LIST_T *list = calloc(1, sizeof(struct LIST));
   list->size = 0;
   list->itemsize = itemsize;
   list->items = 0;

   return list;
}

void listpush(LIST_T *list, void *item)
{
   list->size++;

   if (!list->items)
      list->items = calloc(1, list->itemsize);
   else
      list->items = realloc(list->items, (list->size * list->itemsize));

   list->items[list->size] = item;
}

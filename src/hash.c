#include "hash.h"
#include <stdlib.h>

#define SIZE 300

struct DATAITEM *hasharray[SIZE];

struct DATAITEM *initdummy(void)
{
   struct DATAITEM *dummyitem;
   dummyitem = (struct DATAITEM *) malloc(sizeof(struct DATAITEM));
   dummyitem->key = -1;

   return dummyitem;
}

struct DATAITEM *inithash(struct DATAITEM *item)
{
   item = (struct DATAITEM *) malloc(sizeof(struct DATAITEM));
   return item;
}

int hashcode(int key)
{
   return key % SIZE;
}

struct DATAITEM *search(int key)
{
   int hashindex = hashcode(key);

   while(hasharray[hashindex] != NULL)
   {
      if (hasharray[hashindex]->key == key)
         return hasharray[hashindex];

      ++hashindex;

      hashindex %= SIZE;
   }

   return NULL;
}

void insert(int key, int data, struct DATAITEM *item)
{
   item->data = data;
   item->key = key;

   int hashindex = hashcode(key);

   while(hasharray[hashindex] != NULL && hasharray[hashindex]->key != -1)
   {
      ++hashindex;

      hashindex %= SIZE;
   }

   hasharray[hashindex] = item;
}

struct DATAITEM *delete(struct DATAITEM *item, struct DATAITEM *dummyitem)
{
   int key = item->key;

   int hashindex = hashcode(key);

   while (hasharray[hashindex] != NULL)
   {
      if (hasharray[hashindex]->key == key)
      {
      struct DATAITEM *temp = hasharray[hashindex];

      hasharray[hashindex] = dummyitem;
      return temp;
      }

      ++hashindex;

      hashindex %= SIZE;
   }

   return NULL;
}
